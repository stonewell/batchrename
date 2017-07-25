#pragma once

#include "wx/wx.h"
#include "filename_matcher.h"

enum ScanDirErrorCodes {
    SUCCESS = 0,
    INVALID_DIRECTORY,
    SCAN_DIR_FAIL,
    UNKNOWN_ERROR,
};

ScanDirErrorCodes scan_dir(const wxString & dirToScan,
                           FilenameMatcher & filenameMatcher,
                           bool includeSubDir);
