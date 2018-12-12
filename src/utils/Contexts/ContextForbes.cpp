/*
 * ContextForbes.cpp
 *
 *  Created on: Apr 24, 2014
 *      Author: nek3d
 */

#include "ContextForbes.h"

ContextForbes::ContextForbes() {
	setSortedInput(true);
	setUseMergedIntervals(true);

}

ContextForbes::~ContextForbes() {

}

bool ContextForbes::parseCmdArgs(int argc, char **argv, int skipFirstArgs)
{
	for (_i=_skipFirstArgs; _i < argc; _i++) {
		if (isUsed(_i - _skipFirstArgs)) {
			continue;
		}
		else if (strcmp(_argv[_i], "-s") == 0) {
			if (!handle_s()) return false;
		}
		else if (strcmp(_argv[_i], "-S") == 0) {
			if (!handle_S()) return false;
		}
	}
	return ContextIntersect::parseCmdArgs(argc, argv, _skipFirstArgs);
}

bool ContextForbes::isValidState()
{
	if (!ContextIntersect::isValidState()) {
		return false;
	}
	return true;
}

bool ContextForbes::handle_s() {
	setSameStrand(true);
	_desiredStrand = FileRecordMergeMgr::SAME_STRAND_EITHER;
	markUsed(_i - _skipFirstArgs);
	return true;
}

bool ContextForbes::handle_S() {
    if ((_i+1) < _argc) {
    	bool validChar = false;
    	if (_argv[_i+1][0] == '+') {
			_desiredStrand = FileRecordMergeMgr::SAME_STRAND_FORWARD;
			validChar = true;
    	} else if (_argv[_i+1][0] == '-') {
    		validChar = true;
			_desiredStrand = FileRecordMergeMgr::SAME_STRAND_REVERSE;
    	}
    	if (validChar) {
			markUsed(_i - _skipFirstArgs);
			_i++;
			markUsed(_i - _skipFirstArgs);
			setSameStrand(true);
			return true;
    	}
    }
	_errorMsg = "\n***** ERROR: -S option must be followed by + or -. *****";
	return false;
}
