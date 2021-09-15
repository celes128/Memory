#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclure les en-têtes Windows rarement utilisés

#define IN
#define OUT

inline int failed(int code)
{
	return code != 0;
}

inline int succeeded(int code)
{
	return !failed(code);
}