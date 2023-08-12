/******************************************************************************
 *  Walker.h (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#ifndef EV3_UNIT_WALKER_H_
#define EV3_UNIT_WALKER_H_

class Cockpit;
class WalkerParams;

class Walker {
public:
  Walker(Cockpit* cockpit);

  virtual ~Walker();

  virtual void init();

  virtual void reset();

  virtual void run() = 0;

  virtual const char* getClassName() const = 0;

  void setParams(const WalkerParams& params);

protected:
  bool getWalkerParam(const char* key, int keyLength, double* value);
  void setDriveParam(int leftPWM, int rightPWM);
  double getBrightness() const;

private:
  void* mContext;
};

#endif  // EV3_UNIT_WALKER_H_
