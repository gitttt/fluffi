/*
Copyright 2017-2019 Siemens AG

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Author(s): Abian Blome, Thomas Riedmaier
*/

#pragma once
#include "FluffiMutator.h"

class CommInt;
class TGWorkerThreadState;
class ExternalMutator :
	public FluffiMutator
{
public:
	ExternalMutator(FluffiServiceDescriptor serviceDescriptor, std::string testcaseDirectory, std::string extDirectory, CommInt* commInt = nullptr, TGWorkerThreadState* workerThreadState = nullptr);
	virtual ~ExternalMutator();

	bool isSetupFunctionable();
	std::deque<TestcaseDescriptor> batchMutate(unsigned int numToGenerate, const FluffiTestcaseID parentID, const std::string parentPathAndFilename);
private:
	std::string m_extTestcaseDir;
	CommInt* m_commInt;
	TGWorkerThreadState* m_workerThreadState;
};
