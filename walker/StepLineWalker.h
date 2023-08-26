/******************************************************************************
 *  StepLineWalker.h (for LEGO Mindstorms EV3)
 *  Created on: 2023/07/22
 *  Definition of the Class LineWalker
 *  Author: Risei Kodo
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#ifndef EV3_WALKER_STEP_LINE_WALKER_H_
#define EV3_WALKER_SETP_LINE_WALKER_H_

#include "LineWalker.h"

class StepLineWalker : public LineWalker {
public:
    StepLineWalker(Uptime* uptime, LineMonitor* lineMonitor);

    virtual ~StepLineWalker();

    virtual const char* getClassName() const;

    virtual void reset(const ScenarioParams& params);
 
    virtual bool execute();

    virtual Control get();

private:
    StepLineWalker(const StepLineWalker&);
    StepLineWalker& operator=(const StepLineWalker&);

    LineMonitor* mLine;
    void* mParam;
};

#endif  // EV3_WALKER_STEP_LINE_WALKER_H_