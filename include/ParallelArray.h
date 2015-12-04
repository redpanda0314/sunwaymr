/*
 * ParallelArray.h
 *
 *  Created on: Dec 2, 2015
 *      Author: yupeng
 */

#ifndef PARALLELARRAY_H_
#define PARALLELARRAY_H_

#include <vector>
#include "SunwayMRContext.h"
#include "IteratorSeq.h"
#include "RDD.h"
#include <string>
#include "ParallelArrayPartition.h"
using std::vector;
using std::string;

template <class T>
class ParallelArray : public RDD<T> {
public:
	ParallelArray(SunwayMRContext &c, IteratorSeq<T> &seq, int numSlices);
	vector<Partition> getPartitions();
	vector<string> preferredLocations(Partition &p);
	IteratorSeq<T> iteratorSeq(Partition &p);
	vector< IteratorSeq<T> > slice();
	//data
	IteratorSeq<T> &seq;
	int numSlices;
	int parallelArray_id; 
	static int current_id;
};


#endif /* PARALLELARRAY_H_ */
