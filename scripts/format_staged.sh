#!/bin/bash
#
# format_staged.sh
# Pre-commit hook to format all staged C/C++ files using clang-format (Google style)

# Exit on errors
set -e

# List of file extensions to check
EXTENSIONS="cpp cxx cc c h hpp"

# Get staged files that are Added/Modified (not deleted/renamed)
STAGED_FILES=$(git diff --cached --name-only --diff-filter=AM)

# Nothing staged
if [ -z "$STAGED_FILES" ]; then
  exit 0
fi

# Loop through staged files
for FILE in $STAGED_FILES; do
  # Check extension
  if [[ $FILE =~ \.($EXTENSIONS)$ ]]; then
    if [ -f "$FILE" ]; then
      echo "Formatting $FILE ..."
      clang-format -i -style=Google "$FILE"

      # Re-stage the file after formatting
      git add "$FILE"
    fi
  fi
done

exit 0
