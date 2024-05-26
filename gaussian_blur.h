#include "base_filter.h"

class GaussianBlur : public BaseFilter {
public:
    explicit GaussianBlur(double value);

    void Apply(Image &image) const override;

private:
    double sigma_;
};
