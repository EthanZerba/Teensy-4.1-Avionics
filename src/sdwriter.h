#ifndef SDWRITER_H
#define SDWRITER_H
#include <vector>

void setupSDWriter();
void writeDataToSD(const std::vector<float>& dataPoints);

#endif // SDWRITER_H