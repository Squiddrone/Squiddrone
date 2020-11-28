#!/bin/bash

# Upload to Report.CI
python3 upload_report_ci.py --include='*.xml' --framework=gtest
