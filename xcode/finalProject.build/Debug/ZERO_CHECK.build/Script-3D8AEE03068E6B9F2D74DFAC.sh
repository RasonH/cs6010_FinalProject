#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/lydiayuan/cs6010_FinalProject/xcode
  make -f /Users/lydiayuan/cs6010_FinalProject/xcode/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/lydiayuan/cs6010_FinalProject/xcode
  make -f /Users/lydiayuan/cs6010_FinalProject/xcode/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/lydiayuan/cs6010_FinalProject/xcode
  make -f /Users/lydiayuan/cs6010_FinalProject/xcode/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/lydiayuan/cs6010_FinalProject/xcode
  make -f /Users/lydiayuan/cs6010_FinalProject/xcode/CMakeScripts/ReRunCMake.make
fi

