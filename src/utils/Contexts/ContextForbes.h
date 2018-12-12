/*
 * ContextForbes.h
 *
 *  Created on: Apr 24, 2014
 *      Author: nek3d
 */

#ifndef CONTEXTFORBES_H_
#define CONTEXTFORBES_H_

#include "ContextIntersect.h"

class ContextForbes : public ContextIntersect {
public:
  ContextForbes();
  ~ContextForbes();
	virtual bool parseCmdArgs(int argc, char **argv, int skipFirstArgs);
	virtual bool isValidState();

protected:
	bool handle_s();
	bool handle_S();
};

#endif /* CONTEXTFORBES_H_ */
