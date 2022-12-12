#include <vsomeip/vsomeip.hpp>
#include <iostream>
#include <sstream>
#include <iomanip>

#define SAMPLE_SERVICE_ID 0x1234
#define SAMPLE_INSTANCE_ID 0x5678
#define SAMPLE_METHOD_ID 0x0421
#define SAMPLE_EVENTGROUP_ID 0x06767


std::shared_ptr< vsomeip::application > app;

//callback function to be called when service recieve a message
void on_message(const std::shared_ptr<vsomeip::message> &_request) {

    std::shared_ptr<vsomeip::payload> its_payload = _request->get_payload();
    vsomeip::length_t l = its_payload->get_length();

    // Get payload
    std::stringstream ss;
    for (vsomeip::length_t i=0; i<l; i++) {
       ss << std::setw(2) << std::setfill('0') << std::hex
          << (int)*(its_payload->get_data()+i) << " ";
    }

    std::cout << "SERVICE: Received message with Client/Session ["
        << std::setw(4) << std::setfill('0') << std::hex << _request->get_client() << "/"
        << std::setw(4) << std::setfill('0') << std::hex << _request->get_session() << "] "
        << ss.str() << std::endl;

    // Create response
    std::shared_ptr<vsomeip::message> its_response = vsomeip::runtime::get()->create_response(_request);
    its_payload = vsomeip::runtime::get()->create_payload();
    std::vector<vsomeip::byte_t> its_payload_data;
    for (int i=9; i>=0; i--) {
        its_payload_data.push_back(i % 256);
    }
    its_payload->set_data(its_payload_data);
    its_response->set_payload(its_payload);
    app->send(its_response);
}

int main() {
//create an application
app = vsomeip::runtime::get()->create_application("world");

//initialize application
app->init();

//register for a message
app->register_message_handler(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_METHOD_ID, on_message);

//register as a service
app->offer_service(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID);

//start application
app->start();
return 0;
}

/*
int main() {

const vsomeip::byte_t its_data[] = {0x10};
std::shared_ptr<vsomeip::payload> payload = vsomeip::runtime::get()->create_payload();
payload->set_data(its_data, sizeof(its_data));
std::set<vsomeip::eventgroup_t> group;
group.insert(SAMPLE_EVENTGROUP_ID);
app = vsomeip::runtime::get()->create_application("world");
app->init();
app->register_message_handler(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_METHOD_ID, on_message);
app->offer_service(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID);
app->start();
app->offer_event(SAMPLE_SERVICE_ID,SAMPLE_INSTANCE_ID,SAMPLE_EVENTGROUP_ID,group);
app->notify(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_EVENTGROUP_ID, payload);

}

*/
























