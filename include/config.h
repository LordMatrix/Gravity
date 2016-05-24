#ifndef __CONFIG_H__
#define __CONFIG_H__ 1

#define BALL_TYPE 1
#define GOAL_TYPE 2
#define CONVEYORBELT_TYPE 3
#define SPRING_TYPE 4
#define BOUNCER_TYPE 5
#define CONVEYORBELT_INVERTED_TYPE 6

const int kWinWidth = 1366;
const int kWinHeight = 768;
const int kNumLevels = 6;
const int kStartingLevel = 1;
const float kMenuWidth = 300.0f;

/*
struct {
  int width;
  int height;
} WindowOptions = {kWinWidth, kWinHeight};
*/
#endif /* __CONFIG_H__ */