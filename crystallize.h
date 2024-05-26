#include "base_filter.h"

class Crystallize : public BaseFilter {
public:
    explicit Crystallize(int32_t center_number);

    void Apply(Image &image) const override;

private:
    int32_t center_number_;
};
