/*
 * forbes.h
 *
 *  Created on: Dec 4, 2018
 *      Author: ivargry
 */

#ifndef FORBES_H_
#define FORBES_H_

#include "ContextForbes.h"
#include "intersectFile.h"

class Forbes : public IntersectFile {

public:
	Forbes(ContextForbes *context);
	virtual bool findNext(RecordKeyVector &);
	virtual void processHits(RecordOutputMgr *, RecordKeyVector &) {}
	virtual void cleanupHits(RecordKeyVector &);
	virtual bool finalizeCalculations();
	virtual void  giveFinalReport(RecordOutputMgr *);


protected:
	unsigned long _queryUnion;
	unsigned long _dbUnion;

    unsigned long _intersectionVal;
    unsigned long _unionVal;
    int _numIntersections;

     virtual unsigned long getTotalIntersection(RecordKeyVector &hits);

	virtual ContextForbes *upCast(ContextBase *context) { return static_cast<ContextForbes *>(context); }
	virtual FileRecordMergeMgr *upCastFRM(FileRecordMgr *frm) { return static_cast<FileRecordMergeMgr *>(frm); }


};

#endif /* FORBES_H_ */
