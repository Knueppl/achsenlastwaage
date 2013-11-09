#include "plot_weights.h"
#include <QApplication>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    PlotWeights plot("./weight_notes/");
    plot.show();

    plot.getWeights();

    return app.exec();
}
