#!/bin/bash

# Create lcov report
lcov --capture --directory . --output-file coverage.info
lcov --remove coverage.info '/usr/include/*' --output-file coverage.info # filter system-files
lcov --list coverage.info # debug info
# Uploading report to CodeCov
bash <(curl -s https://codecov.io/bash) -f coverage.info || echo "Codecov did not collect coverage reports"
