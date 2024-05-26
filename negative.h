#include "base_filter.h"

class Negative : public BaseFilter {
public:
    void Apply(Image &image) const override;
};
