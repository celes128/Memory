#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclure les en-têtes Windows rarement utilisés

#define IN
#define OUT

typedef int Result;
const Result kSuccess = 0;
const Result kFailure = -1;

inline bool ok(Result code) { return kSuccess == code; }
inline bool failed(Result code) { return !(ok(code)); }
