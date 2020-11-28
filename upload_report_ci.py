#!/usr/bin/env python

import os
import sys
import argparse
import subprocess  # nosec
import re
import fnmatch
import json
import urllib

from urllib.parse import urlencode
from urllib.request import Request, urlopen

env = os.environ


class BColors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'


parser = argparse.ArgumentParser()

parser.add_argument("-i", "--include", nargs='+',
                    help="Files to include, can cointain unix-style wildcard. (default *.xml)",
                    default=["*.xml", "*.json", "*.trx", "*.tap"])
parser.add_argument("-x", "--exclude", nargs='+', help="Files to exclude, can cointain unix-style wildcard.",
                    default=[])
parser.add_argument("-l", "--file_list", nargs='+',
                    help="Explicit file list, if given include and exclude are ignored.", default=None)

parser.add_argument("-t", "--token",
                    help="Token to authenticate (not needed for public projects on appveyor, travis and circle-ci")
parser.add_argument("-n", "--name",
                    help="Custom defined name of the upload when commiting several builds with the same ci system")
parser.add_argument("-f", "--framework",
                    choices=["boost", "junit", "testng", "xunit", "cmocka", "unity", "criterion", "bandit",
                             "catch", "cpputest", "cute", "cxxtest", "gtest", "qtest", "go", "testunit", "rspec",
                             "minitest",
                             "nunit", "mstest", "xunitnet", "phpunit", "pytest", "pyunit", "mocha", "ava", "tap",
                             "tape", "qunit", "doctest", "nunit"],
                    help="The used unit test framework - if not provided the script will try to determine it")
parser.add_argument("-r", "--root_dir",
                    help="The root directory of the git-project, to be used for aligning paths properly. "
                         "Default is the git-root.")
parser.add_argument("-s", "--ci_system", help="Set the CI System manually. Should not be needed")
parser.add_argument("-b", "--build_id",
                    help="The identifer The Identifer for the build. When used on a CI system this will be "
                         "automatically generated.")
parser.add_argument("-a", "--sha", help="Specify the commit sha - normally determined by invoking git")
parser.add_argument("-c", "--check_run", help="The check-run id used by github, used to update reports.")
parser.add_argument("-d", "--id_file", help="The file to hold the check id given by github.",
                    default=".report-ci-id.json")
parser.add_argument("-D", "--define", help="Define a preprocessor token for the name lookup.", nargs='+')
parser.add_argument("-p", "--preset", help="Select a definition & include preset from .report-ci.yaml.")
parser.add_argument("-m", "--merge", help="Merge similar annotations from different check-runs.")

args = parser.parse_args()

if not args.check_run:
    try:
        args.check_run = json.loads(open(args.id_file, "r").read())["github"]
    except Exception as e:
        print(e)

root_dir = None
branch = None
service = None
pr = None
commit = None
build = None
build_url = None
search_in = None
slug = None
run_name = args.name
build_id = None
account_name = None
os_name = None

if env.get("GITHUB_ACTIONS") == "true":
    print(BColors.HEADER + "    Github actions CI detected." + BColors.ENDC)
    # https://help.github.com/en/actions/configuring-and-managing-workflows/using-environment-variables
    service = "github-actions"

    build_id = env.get("GITHUB_RUN_ID")
    commit = env.get("GITHUB_SHA")
    slug = env.get("GITHUB_REPOSITORY")
    account_name = env.get("GITHUB_ACTOR")
    root_dir = env.get("GITHUB_WORKSPACE")
    branch = env.get("GITHUB_REF")
    if branch:
        branch = os.path.basename(branch)

else:
    print(BColors.HEADER + "    No CI detected." + BColors.ENDC)

if args.root_dir:
    root_dir = args.root_dir

if args.sha:
    commit = args.sha
if not commit:
    commit = subprocess.check_output(["/bin/git", "rev-parse", "HEAD"]).decode().replace('\n', '')  # nosec

print(BColors.OKBLUE + "    Commit hash: " + commit + BColors.ENDC)

if not root_dir:
    root_dir = subprocess.check_output(["/bin/git", "rev-parse", "--show-toplevel"]).decode().replace('\n', '')  # nosec

print(BColors.OKBLUE + "    Root dir: " + root_dir + BColors.ENDC)

owner, repo = None, None
if slug:
    try:
        (owner, repo) = slug.split('/')
    except Exception as e:
        print(BColors.WARNING + "Invalid Slug: '{0}'".format(slug) + BColors.ENDC)

if not owner or not repo:
    remote_v = subprocess.check_output(["/bin/git", "remote", "-v"]).decode()  # nosec
    match = re.search(r"(?:https://|ssh://git@)github.com/([-_A-Za-z0-9]+)/((?:(?!\.git(?:\s|$))[-._A-Za-z0-9])+)",
                      remote_v)
    if match:
        owner = match.group(1)
        repo = match.group(2)
    else:
        match = re.search(r"git@github\.com:([-_A-Za-z0-9]+)/((?:(?!\.git(?:\s|$))[-._A-Za-z0-9])+)", remote_v)
        owner = match.group(1)
        repo = match.group(2)

print(BColors.OKBLUE + "    Project: " + owner + '/' + repo + BColors.ENDC)


def match_file(file_abs):
    match = False
    file = os.path.relpath(file_abs)
    for inc in args.include:
        if fnmatch.fnmatch(file, inc) or fnmatch.fnmatch(file_abs, inc):
            match = True
            break

    for exc in args.exclude:
        if fnmatch.fnmatch(file, exc) or fnmatch.fnmatch(file_abs, exc):
            match = False
            break

    return match


boost_test = []
junit_test = []
xunit_test = []
testng_test = []
criterion_test = []
complete_content = []
file_list = []
bandit = []
catch_test = []
cxxtest = []
qtest = []
go_test = []
testunit = []
rspec = []
phpunit = 0
pytest = 0
mocha = []

tap_test = []
ava = 0

mstest = []
xunitnet = []
nunit = []
doctest = []

if not args.file_list:
    for wk in os.walk(root_dir):
        (path, subfolders, files) = wk
        if fnmatch.fnmatch(path, "*/.git*"):
            continue
        for file in files:
            abs_file = os.path.join(path, file)
            file_list.append(abs_file)
else:
    for file in args.file_list:
        abs_ = os.path.abspath(file)
        if not os.path.isfile(abs_):
            print(BColors.FAIL + "Could not find file '" + file + "'" + BColors.ENDC)
            exit(1)
        else:
            file_list.append(abs_)

for abs_file in file_list:
    if match_file(abs_file):
        content = None

        ext = os.path.splitext(abs_file)[1].lower()
        binary_content = open(abs_file, "rb").read()
        try:
            content = binary_content.decode('ascii')
        except UnicodeDecodeError:
            try:
                content = binary_content.decode('utf-8').encode("ascii", "ignore").decode('ascii')
            except UnicodeDecodeError:
                try:
                    content = binary_content.decode('utf-16').encode("ascii", "ignore").decode('ascii')
                except UnicodeDecodeError:
                    print(
                        BColors.FAIL + "Can't figure out encoding of file " + abs_file + ", ignoring it" + BColors.ENDC)
                    continue

        complete_content.append(content)

        if ext == ".xml":
            if re.match(r"(<\?[^?]*\?>\s*)?<(?:TestResult|TestLog)>\s*<TestSuite", content):
                print("    Found " + abs_file + " looks like boost.test")
                boost_test.append(content)
                continue

            if re.match(r"(<\?[^?]*\?>\s*)?<TestCase", content) and (
                    content.find("<QtVersion>") != -1 or content.find("<qtversion>") != -1):
                print("    Found " + abs_file + ", looks like qtest")
                qtest.append(content)
                continue

            if re.match(
                    r'(<\?[^?]*\?>\s*)?<!-- Tests compiled with Criterion v[0-9.]+ -->\s*<testsuites name="Criterion Tests"',
                    content):
                print("    Found " + abs_file + ", looks like criterion")
                criterion_test.append(content)
                continue

            if re.match(r"(<\?[^?]*\?>\s*)?(<testsuites>\s*)?<testsuite[^>]", content):  # xUnit thingy
                if content.find('"java.version"') != -1 and (
                        content.find('org.junit') != -1 or content.find('org/junit') != -1 or
                        content.find('org\\junit') != -1):
                    print("    Found " + abs_file + ", looks like JUnit")
                    junit_test.append(content)
                elif content.find('"java.version"') != -1 and (
                        content.find('org.testng') != -1 or content.find('org/testng') != -1 or
                        content.find('org\    estng') != -1):
                    print("    Found " + abs_file + ", looks like TestNG")
                    testng_test.append(content)
                elif content.find('"java.version"') == -1 and content.find('<testsuite name="bandit" tests="') != -1:
                    print("    Found " + abs_file + ", looks like Bandit")
                    bandit.append(content)
                elif content.find('.php') != -1:
                    print("    Found " + abs_file + ", looks like PHPUnit")
                    phpunit += 1
                    xunit_test.append(content)
                elif content.find('.py') != -1:
                    print("    Found " + abs_file + ", looks like PyTest")
                    pytest += 1
                    xunit_test.append(content)
                else:
                    print("    Found " + abs_file + ", looks like some xUnit")
                    xunit_test.append(content)
                continue

            if re.match(r'(<\?[^?]*\?>\s*)?<Catch\s+name=', content):
                print("    Found " + abs_file + ", looks like catch")
                catch_test.append(content)
                continue
            if re.match(r'(<\?[^?]*\?>\s*)?<stream>\s*<ready-test-suite>', content):
                print("    Found " + abs_file + ", looks like TestUnit")
                testunit.append(content)
                continue
            if re.match(
                    r'(<\?[^?]*\?>\s*)?(<!--This file represents the results of running a test suite-->)?<test-results\s+name',
                    content) or \
                    re.match(r'(<\?[^?]*\?>\s*)?<test-run id="2"', content):
                print("    Found " + abs_file + ", looks like NUnit")
                nunit.append(content)
                continue
            if re.match(r'(<\?[^?]*\?>)?\s*<assemblies', content):
                print("    Found " + abs_file + ", looks like xUnit.net")
                xunitnet.append(content)
                continue

            if re.match(r'(<\?[^?]*\?>)?\s*<doctest', content):
                print("    Found " + abs_file + ", looks like doctest")
                doctest.append(content)
                continue

        elif ext == ".json" and re.match(r"\s*({|\[)", content):  # Might be JSON, let's see if it fits go
            try:
                lines = content.splitlines()
                json_lines = [json.loads(ln) for ln in lines]
                if all(val in json_lines[0] for val in ["Time", "Action", "Package"]):  # assumption
                    print("Found " + abs_file + ", looks like GoTest")
                    go_test = go_test + [json.loads(ln) for ln in lines]
                    continue
            except Exception as e:
                print(e)
            try:
                data = json.loads(content)

                if "version" in data and "examples" in data and "summary" in data and "summary_line" in data:
                    print("Found " + abs_file + ", looks like RSpec")
                    rspec.append(data)
                    continue
                if "stats" in data and "tests" in data and "pending" in data and "passes" in data and "failures" in data:
                    print("Found " + abs_file + ", looks like Mocha")
                    mocha.append(data)
                    continue

            except Exception as e:
                print(e)

            # data = loadJson(content)
        elif ext == ".trx" and re.match(r"(<\?[^?]*\?>\s*)?<TestRun", content):
            print("Found " + abs_file + ", looks like MsTest")
            mstest.append((abs_file, content))

        elif ext == ".tap" and re.match(r"TAP version \d+", content):  # is Test anything protocol
            if re.match(r"ava[\\\/]cli.js", content):
                print("Found " + abs_file + ", looks like AVA")
                ava += 1
            else:
                print("Found " + abs_file + ", looks like TAP")
            tap_test.append(content)

upload_content = ""
content_type = ""

if not args.framework:
    # check for different test frameworks

    if len(testng_test) > 0:
        framework = "testng"
        print(BColors.HEADER + "TestNG detected" + BColors.ENDC)

    elif len(junit_test) > 0:
        framework = "junit"
        print(BColors.HEADER + "JUnit detected" + BColors.ENDC)

    elif len(bandit) > 0:
        framework = "bandit"
        print(BColors.HEADER + "Bandit detected" + BColors.ENDC)

    elif phpunit > 0:
        framework = "phpunit"
        print(BColors.HEADER + "PHPUnit detected" + BColors.ENDC)

    elif pytest > 0:
        framework = "pytest"
        print(BColors.HEADER + "PyTest detected" + BColors.ENDC)

    elif len(xunit_test) > 0:
        framework = "xunit"
        print(BColors.HEADER + "Unspecified xUnit detected" + BColors.ENDC)

    elif len(boost_test) > 0:
        framework = "boost"
        print(BColors.HEADER + "Boost.test detected" + BColors.ENDC)

    elif len(criterion_test) > 0:
        framework = "criterion"
        print(BColors.HEADER + "Criterion detected" + BColors.ENDC)

    elif len(catch_test) > 0:
        framework = "catch"
        print(BColors.HEADER + "Catch detected" + BColors.ENDC)

    elif len(cxxtest) > 0:
        framework = "cxxtest"
        print(BColors.HEADER + "CxxTest detected" + BColors.ENDC)

    elif len(qtest) > 0:
        framework = "qtest"
        print(BColors.HEADER + "QTest detected" + BColors.ENDC)

    elif len(go_test) > 0:
        framework = "go-test"
        print(BColors.HEADER + "Go detected" + BColors.ENDC)

    elif len(testunit) > 0:
        framework = "testunit"
        print(BColors.HEADER + "TestUnit detected" + BColors.ENDC)

    elif len(mstest) > 0:
        framework = "mstest"
        print(BColors.HEADER + "MSTest detected" + BColors.ENDC)

    elif len(nunit) > 0:
        framework = "nunit"
        print(BColors.HEADER + "NUnit detected" + BColors.ENDC)

    elif len(xunitnet) > 0:
        framework = "xunitnet"
        print(BColors.HEADER + "XUnit.net detected" + BColors.ENDC)

    elif len(rspec) > 0:
        framework = "rspec"
        print(BColors.HEADER + "RSpec detected" + BColors.ENDC)

    elif len(mocha) > 0:
        framework = "mocha"
        print(BColors.HEADER + "Mocha detected" + BColors.ENDC)

    elif ava > 0:
        framework = "ava"
        print(BColors.HEADER + "AVA detected" + BColors.ENDC)

    elif len(tap_test) > 0:
        framework = "tap"
        print(BColors.HEADER + "Unspecificed TAP detected" + BColors.ENDC)

    elif len(doctest) > 0:
        framework = "doctest"
        print(BColors.HEADER + "Doctest detected" + BColors.ENDC)

    else:

        print(BColors.FAIL + "No framework selected and not detected." + BColors.ENDC)
        exit(1)
else:
    framework = args.framework
    print(BColors.HEADER + framework + " selected" + BColors.ENDC)

if framework == "gtest":
    content_type = "text/xml"
    upload_content = "<root>" + "".join(xunit_test) + "</root>"
    if not run_name:
        run_name = "GoogleTest"

upload_content = upload_content.strip()
if len(upload_content) == 0:
    print(BColors.FAIL + " No test data to upload.")
    exit(1)

if service and not args.name and run_name:
    if os_name:
        run_name += " [" + service + ", " + os_name + "]"
    else:
        run_name += " [" + service + "]"

headers = {}

query = {
    'framework': framework,
    'owner': owner,
    'repo': repo,
    'head-sha': commit,
    'root-dir': root_dir,
    'branch': branch,
    'account-name': account_name,
}

if run_name:
    query['run-name'] = run_name
if args.check_run:
    query['check-run-id'] = args.check_run
if args.preset:
    query['preset'] = args.preset
if args.define:
    query['define'] = args.define
if args.merge:
    query["merge"] = args.merge

url = "https://api.report.ci/publish/"

url = urllib.request.urlopen(url).geturl()  # nosec

if service and service in ["travis-ci", "appveyor", "circle-ci", "github-actions"] and args.token is None:
    query["build-id"] = build_id
    url += service + "/"

if sys.version_info >= (3, 0):
    upload_content = bytes(upload_content, "utf8")

if args.check_run and not args.name and 'run-name' in query:
    del query['run-name']

request = Request(url + "?" + urlencode(query), upload_content, headers)
if args.token:
    request.add_header("Authorization", "Bearer " + args.token)
if content_type:
    request.add_header("Content-Type", content_type)

if args.check_run:
    request.get_method = lambda: 'PATCH'

try:
    response = urlopen(request).read().decode()  # nosec
    print(BColors.OKGREEN + "Published: '{0}".format(response) + BColors.ENDC)
    res = json.loads(response)
    ch_id = str(res["id"])
    print('Uploaded check_run https://report.ci/reports/gh/{}/{}/rep/{}'.format(owner, repo, ch_id))
    open(args.id_file, 'w').write(response)
    exit(0)

except Exception as e:
    print(BColors.FAIL + 'Publishing failed: {0}'.format(e) + BColors.ENDC)
    print(BColors.FAIL + 'url: {}'.format(url) + BColors.ENDC)
    print(BColors.FAIL + 'owner: {}'.format(owner) + BColors.ENDC)
    print(BColors.FAIL + 'repo: {}'.format(repo) + BColors.ENDC)
    print(BColors.FAIL + 'ch_id: {}'.format(ch_id) + BColors.ENDC)
    print(e)
    exit(1)
