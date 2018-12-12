/*
 * forbes.cpp
 *
 *  Created on: Apr 24, 2015
 *      Author: nek3d
 */

#include "forbes.h"

Forbes::Forbes(ContextForbes *context)
: IntersectFile(context),
 _queryUnion(0),
 _dbUnion(0),
 _intersectionVal(0),
 _unionVal(0),
 _numIntersections(0)
{

}

bool Forbes::findNext(RecordKeyVector &hits) {
	if (nextSortedFind(hits)) {
		checkSplits(hits);
		_intersectionVal += getTotalIntersection(hits);
		return true;
	}
	return false;
}

void Forbes::cleanupHits(RecordKeyVector &hits)
{
//	upCastFRM(_queryFRM)->deleteMergedRecord(hits);
}


bool Forbes::finalizeCalculations() {
	_sweep->closeOut();
	_queryUnion = _sweep->getQueryTotalRecordLength();
	_dbUnion = _sweep->getDatabaseTotalRecordLength();

	_unionVal = _queryUnion + _dbUnion;
	return true;
}

void  Forbes::giveFinalReport(RecordOutputMgr *outputMgr) {
	// header
	outputMgr->checkForHeader();

	cout << "intersection\tunion-intersection\tforbes\tn_intersections" << endl;

	unsigned long adjustedUnion = _unionVal - _intersectionVal;
	unsigned int genomeSize = 3000000000;
	unsigned long forbesVal = (float) _intersectionVal / ( (float) _queryUnion / genomeSize * (float) _dbUnion / _queryUnion );

	cout << _intersectionVal;
	cout << _queryUnion;
	cout << _dbUnion;

	cout << _intersectionVal << "\t" << adjustedUnion << "\t" <<
			(float)forbesVal << "\t" << _numIntersections << endl;
}

unsigned long Forbes::getTotalIntersection(RecordKeyVector &hits)
{
	unsigned long intersection = 0;
	Record *key = hits.getKey();
	int keyStart = key->getStartPos();
	int keyEnd = key->getEndPos();

	int hitIdx = 0;
	for (RecordKeyVector::iterator_type iter = hits.begin(); iter != hits.end(); iter = hits.next()) {
		Record *currRec = *iter;
		int maxStart = max(currRec->getStartPos(), keyStart);
		int minEnd = min(currRec->getEndPos(), keyEnd);
		if (_context->getObeySplits()) {
			intersection += upCast(_context)->getSplitBlockInfo()->getOverlapBases(hitIdx);
			hitIdx++;
		} else {
			intersection += (unsigned long)(minEnd - maxStart);
		}
	}
	_numIntersections += (int)hits.size();
	return intersection;
}

