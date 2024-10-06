#include "./math-model.hpp"
#include "./customer.hpp"
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

int main() {
    cout << "Running tests...\n" << endl;

    cout << "Testing MathModel..." << endl;

    MathModel model = MathModel(2, 3, 2);

    cout << fixed << setprecision(numeric_limits<float>::max_digits10);

    if (model.getIdleTime() != 0.5) cout << "MathModel Failed - Idle Time: " << model.getIdleTime() << " != 0.5" << endl;
    if (model.getAvgNumPeople() != 0.75) cout << "MathModel Failed - Avg Num People: " << model.getAvgNumPeople() << " != 0.75" << endl;
    if (model.getAvgTotalTime() != 0.375) cout << "MathModel Failed - Avg Total Time: " << model.getAvgTotalTime() << " != 0.375" << endl;
    if (model.getAvgQueueNum() < 0.083 || model.getAvgQueueNum() > 0.084) cout << "MathModel Failed - Avg Queue Num: " << model.getAvgQueueNum() << " != 0.083" << endl;
    if (model.getAvgTimeInQueue() < 0.0416 || model.getAvgTimeInQueue() > 0.0417) cout << "MathModel Failed - Avg Time In Queue: " << model.getAvgTimeInQueue() << " != 0.0417" << endl;

    model.setLambda(1);
    model.setMu(1);
    model.setNumServiceChannels(1);
    model.calculateNewValues(2, 3, 2);

    if (model.getIdleTime() != 0.5) cout << "MathModel Failed - Idle Time: " << model.getIdleTime() << " != 0.5" << endl;
    if (model.getAvgNumPeople() != 0.75) cout << "MathModel Failed - Avg Num People: " << model.getAvgNumPeople() << " != 0.75" << endl;
    if (model.getAvgTotalTime() != 0.375) cout << "MathModel Failed - Avg Total Time: " << model.getAvgTotalTime() << " != 0.375" << endl;
    if (model.getAvgQueueNum() < 0.083 || model.getAvgQueueNum() > 0.084) cout << "MathModel Failed - Avg Queue Num: " << model.getAvgQueueNum() << " != 0.083" << endl;
    if (model.getAvgTimeInQueue() < 0.0416 || model.getAvgTimeInQueue() > 0.0417) cout << "MathModel Failed - Avg Time In Queue: " << model.getAvgTimeInQueue() << " != 0.0417" << endl;

    cout << "MathModel tests complete\n" << endl;



    cout << "Running Customer tests..." << endl;

    Customer cust = Customer();
    cust.setArrivalTime(123.123);
    cust.setStartOfServiceTime(321.321);
    cust.setDepartureTime(555.555);

    if (cust.getArrivalTime() < 123.123 || cust.getArrivalTime() > 123.124) cout << "Customer Failed - Arrival Time: " << cust.getArrivalTime() << " !=" << " 123.123" << endl;
    if (cust.getStartOfServiceTime() < 321.321 || cust.getStartOfServiceTime() > 321.322) cout << "Customer Failed - Start Of Service Time: " << cust.getStartOfServiceTime() << " !=" << " 321.321" << endl;
    if (cust.getDepartureTime() < 555.554 || cust.getDepartureTime() > 555.555) cout << "Customer Failed - Departure Time: " << cust.getDepartureTime() << " !=" << " 555.555" << endl;

    cout << "Customer tests complete\n" << endl;

    cout << "All tests complete" << endl;
}