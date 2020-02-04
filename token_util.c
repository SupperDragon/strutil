#include "token_util.h"
#include "common_util.h"
#include <regex.h>
#include <string.h>

int split_by_str(const char* src, const char* delim, char* dst[], int n)
{
	int idx = 0;
	int delim_len = 0;
	char* pos = NULL;

	if (empty_str(src) || !dst || n <= 0) {
		return -1;
	}
	if (empty_str(delim)) {
		dst[idx] = strdup(src);
		return ++idx;
	}

	delim_len = strlen(delim);
	for (idx = 0; idx < n; ++idx) {
		if ((pos = strstr(src, delim)) == NULL) {
			dst[idx] = strdup(src);
			return ++idx;
		}

		dst[idx] = strndup(src, pos - src);
		src = pos + delim_len;
	}

	return 0;
}

int split_by_reg(const char* src, const char* pattern, char* dst[], int n)
{
	int ret = 0;
	int idx = 0;
	regex_t regex;
	regmatch_t match[1];

	if (empty_str(src) || !dst || n <= 0) {
		return -1;
	}
	if (empty_str(pattern)) {
		dst[idx] = strdup(src);
		return ++idx;
	}
	if ((ret = regcomp(&regex, pattern, REG_EXTENDED)) != 0) {
		return -1;
	}
	for (idx = 0; idx < n; ++idx) {
		if ((ret = regexec(&regex, src, 1, match, 0)) == REG_NOMATCH) {
			dst[idx] = strdup(src);
			break;
		}
		dst[idx] = strndup(src, match[0].rm_so);
		src += match[0].rm_eo;
	}

	regfree(&regex);
	return ++idx;
}

void free_tokens(char* tokens[], int n)
{
	for (--n; n >= 0; --n) {
		if (tokens[n]) {
			FREE_PTR(tokens[n]);
		}
	}
}

void trim_tokens(char* tokens[], int n) {
	for (--n; n >= 0; --n) {
		trim(tokens[n]);
	}
}