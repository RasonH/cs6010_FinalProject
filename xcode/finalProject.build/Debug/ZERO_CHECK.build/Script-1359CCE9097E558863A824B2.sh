#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/rasonhung/MSD/cs6010/FinalProject/myGithubRepo/xcode
  make -f /Users/rasonhung/MSD/cs6010/FinalProject/myGithubRepo/xcode/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/rasonhung/MSD/cs6010/FinalProject/myGithubRepo/xcode
  make -f /Users/rasonhung/MSD/cs6010/FinalProject/myGithubRepo/xcode/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/rasonhung/MSD/cs6010/FinalProject/myGithubRepo/xcode
  make -f /Users/rasonhung/MSD/cs6010/FinalProject/myGithubRepo/xcode/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/rasonhung/MSD/cs6010/FinalProject/myGithubRepo/xcode
  make -f /Users/rasonhung/MSD/cs6010/FinalProject/myGithubRepo/xcode/CMakeScripts/ReRunCMake.make
fi

