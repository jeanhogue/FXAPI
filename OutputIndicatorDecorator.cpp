#include "OutputIndicatorDecorator.h"


OutputIndicatorDecorator::OutputIndicatorDecorator(IFXIndicator *_decoree, const std::string &outFilename)
{
    decoree = _decoree;
    out.open(outFilename.c_str());
}

OutputIndicatorDecorator::~OutputIndicatorDecorator()
{
    out.close();
}

void OutputIndicatorDecorator::OnNewBar(double sample, int timeIndex)
{
    decoree->OnNewBar(sample, timeIndex);
    out << sample << " " << decoree->GetCurrentValue() << std::endl;
}