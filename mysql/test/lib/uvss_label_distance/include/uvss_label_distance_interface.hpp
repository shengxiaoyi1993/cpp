#ifndef UVSS_LABEL_DISTANCE_INTERFACE
#define UVSS_LABEL_DISTANCE_INTERFACE 1

namespace uvsslabeldistance {

int uld_CalculateLabel(const char *image_path, float *label);

float uld_Distance(float *label1, float *label2);
}  // namespace uvsslabeldistance

#endif