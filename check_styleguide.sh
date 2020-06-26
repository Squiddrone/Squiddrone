#!/bin/bash

set -euo pipefail

find . \( -name '*.hpp' -o -name '*.cpp' \) -exec clang-format -i {} +

not_correct_list=$(git ls-files -m)

if [[ -z $not_correct_list ]]; then
  echo "No styleguide violation with clang-format found.";
  exit 0;
else
  echo "Please check following files:";
  for f in $not_correct_list; do
    echo "$f"
    git --no-pager diff "$f"
  done
fi

git reset HEAD --hard
exit 1;
