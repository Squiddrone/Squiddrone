#!/bin/bash

# Upload to Report.CI
curl -s https://report.ci/upload.py | python - --include='*.xml' --framework=gtest
