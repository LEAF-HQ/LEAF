class AnalysisModule {
public:

    virtual bool process(Event & event) = 0;
    virtual ~AnalysisModule() = default;
};
