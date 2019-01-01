#include <uWS/uWS.h>
#include <iostream>
#include "json.hpp"
#include "PID.h"
#include <math.h>

// for convenience
using json = nlohmann::json;

// For converting back and forth between radians and degrees.
constexpr double pi() { return M_PI; }
double deg2rad(double x) { return x * pi() / 180; }
double rad2deg(double x) { return x * 180 / pi(); }

// Checks if the SocketIO event has JSON data.
// If there is data the JSON object in string format will be returned,
// else the empty string "" will be returned.
std::string hasData(std::string s) {
  auto found_null = s.find("null");
  auto b1 = s.find_first_of("[");
  auto b2 = s.find_last_of("]");
  if (found_null != std::string::npos) {
    return "";
  }
  else if (b1 != std::string::npos && b2 != std::string::npos) {
    return s.substr(b1, b2 - b1 + 1);
  }
  return "";
}

int main()
{
  uWS::Hub h;

  PID pid;
  // TODO: Initialize the pid variable.
  //double init_Kp = -1 ; double init_Ki = 0 ; double init_Kd = 0 ; // as per Q+A video ....big oscilations before first corner
  //double init_Kp = -0.5 ; double init_Ki = 0 ; double init_Kd = -0.5 ; // as per Q+A video.. similar to first terrible before first corner
  // I am hardcoding the values so the reviewer can see what I experimented with
  // I am beginning by only adjusting one variable and in broad strokes or big steps
  // After I try these values I will pick best and refine
  //double init_Kp = -0.25 ; double init_Ki = 0 ; double init_Kd = 0 ; //adjusting Kp off road before first corner
  //double init_Kp = -0.10 ; double init_Ki = 0 ; double init_Kd = 0 ; //adjusting Kp almost makes complete first corner
  //double init_Kp = 0.10 ; double init_Ki = 0 ; double init_Kd = 0 ; //adjusting Kp.. round in circles before first corner
  //double init_Kp = 0.25 ; double init_Ki = 0 ; double init_Kd = 0 ; //adjusting Kp..similar to previuos round in circles immediately
  //double init_Kp = 0.50 ; double init_Ki = 0 ; double init_Kd = 0 ; //adjusting Kp 0.10 and 0.25 and 0.5 all very similar circles immediately
  
  
  // I am trying using  same 4 levels  Kp with 4 levels of Kd
  //double init_Kp = -0.25 ; double init_Ki = 0 ; double init_Kd = -0.5 ; //..starts OK but major oscilations makes it to end of first corner
  //double init_Kp = -0.25 ; double init_Ki = 0 ; double init_Kd = -0.25 ; //worse than previuos
  //double init_Kp = -0.25 ; double init_Ki = 0 ; double init_Kd = 0.5 ; // worse again than previuos
  //double init_Kp = -0.25 ; double init_Ki = 0 ; double init_Kd = 0.25 ; a little better then previuos but doesn't make first corner
  // of above 4 first best
  
  
  //double init_Kp = -0.10 ; double init_Ki = 0 ; double init_Kd = -0.5 ; // MASSIVE IMPROVEMENT might pass touches red and white kerb but does lap 
  //double init_Kp = -0.10 ; double init_Ki = 0 ; double init_Kd = -0.25 ; // a lot worse than previuos bigger osicaltions and hits kerb on brige better than first batch of 4 but much worse than previous
  //double init_Kp = -0.10 ; double init_Ki = 0 ; double init_Kd = 0.5 ; // worse again than previuos similar to first one or two that made the first corner
  //double init_Kp = -0.10 ; double init_Ki = 0 ; double init_Kd = 0.25 ; // similar to previous off track before first corner
  //out of above batch of 4 the first was by far the best
  
  //double init_Kp = 0.10 ; double init_Ki = 0 ; double init_Kd = -0.5 ; // terrible almost immediate truned off track not quite as bad as the immediate circles but very bad
  //double init_Kp = 0.10 ; double init_Ki = 0 ; double init_Kd = -0.25 ; // quite similar to previous off track in 2 second
  //double init_Kp = 0.10 ; double init_Ki = 0 ; double init_Kd = 0.5 ; // almost same as previuos
  //double init_Kp = 0.10 ; double init_Ki = 0 ; double init_Kd = 0.25 ; // almost same as previous
  //above 4 all bad
  
  
  //double init_Kp = 0.25 ; double init_Ki = 0 ; double init_Kd = -0.5 ; // immedately off track
  //double init_Kp = 0.25 ; double init_Ki = 0 ; double init_Kd = -0.25 ; // immediately off track
  //double init_Kp = 0.25 ; double init_Ki = 0 ; double init_Kd = 0.5 ; // same as previuso 2
  //double init_Kp = 0.25 ; double init_Ki = 0 ; double init_Kd = 0.25 ; // same as prevous 3 ....terrible
  
  //double init_Kp = 0.50 ; double init_Ki = 0 ; double init_Kd = -0.50 ; // like previuos 4 I am wondering is the complier working results are so similar...
  //double init_Kp = 0.50 ; double init_Ki = 0 ; double init_Kd = -0.25 ; // like prevoiuos 5!
  //double init_Kp = 0.50 ; double init_Ki = 0 ; double init_Kd = 0.5 ; // like previuos 6!
  //double init_Kp = 0.50 ; double init_Ki = 0 ; double init_Kd = 0.25 ; // like previuos 7!

  
  //taking my best and varying around that in small steps 
  // I have not tested beyoind 0.5 yet so will vary that
  //double init_Kp = -0.10 ; double init_Ki = 0 ; double init_Kd = -0.75 ; //slightly better than previuos best small touches on red and white kerbs...might be good enough to pass
  //double init_Kp = -0.10 ; double init_Ki = 0 ; double init_Kd = -1.0 ; //slightly maybe better than previuos slightly smaller touches on red and white kerb
  //double init_Kp = -0.10 ; double init_Ki = 0 ; double init_Kd = -1.5 ; //slightly better than last one slightly less touches of red and white but sttering seems harsher...better chace of passing but less pleasent to be in...
  //double init_Kp = -0.10 ; double init_Ki = 0 ; double init_Kd = -2.0; //slightly better again almost no touching of red and white kerbs but steering slightly harsher than previuos
  
  //decide to continus al long as fidning improvment
  //double init_Kp = -0.10 ; double init_Ki = 0 ; double init_Kd = -2.5; //as per trend slightly less touching on red and white kerbs but harsher steering
  //double init_Kp = -0.10 ; double init_Ki = 0 ; double init_Kd = -3.0; //I think this will pass does nit touch red and white but does touch yellow line before red and white...need to check rubric
  //double init_Kp = -0.10 ; double init_Ki = 0 ; double init_Kd = -3.5; //I think this is slightly better than previouos
  //double init_Kp = -0.10 ; double init_Ki = 0 ; double init_Kd = -4.0; //possibly a little better than previuos
  //double init_Kp = -0.10 ; double init_Ki = 0 ; double init_Kd = -5.0; //jumping to 5 looking for potential imporvemnt..not sure similar maybe steering more wobbly
  //double init_Kp = -0.10 ; double init_Ki = 0 ; double init_Kd = -6.0; //steering a bit harcher buit avoid kerbs
  
  //double init_Kp = -0.15 ; double init_Ki = 0 ; double init_Kd = -6.0; //steering a bit hard BUT might be the best so far
  //double init_Kp = -0.05 ; double init_Ki = 0 ; double init_Kd = -6.0; //slightly worse on red kerbs
  //double init_Kp = -0.15 ; double init_Ki = 0 ; double init_Kd = -5.0;//good contenter for best does not touch red kerbs but does yellow lines and not as smooth as firt good one but better on kerbs
  //double init_Kp = -0.15 ; double init_Ki = 0 ; double init_Kd = -4.0; // this seems the best so far
  
  //more fine tuning
  //double init_Kp = -0.17 ; double init_Ki = 0 ; double init_Kd = -4.0; // best so far
  //double init_Kp = -0.13 ; double init_Ki = 0 ; double init_Kd = -4.0; // maybe harsher steering than last
  
  //going with double init_Kp = -0.17 ; double init_Ki = 0 ; double init_Kd = -4.0;
  double init_Kp = -0.17 ; double init_Ki = 0 ; double init_Kd = -4.0;
  //now to increase speed!!! somewhere below.....line 149 msgJson["throttle"] = 0.5;
  //crashes at throttle 0.5 on red and white kerbs
  
  pid.Init(init_Kp, init_Ki, init_Kd) ;

  h.onMessage([&pid](uWS::WebSocket<uWS::SERVER> ws, char *data, size_t length, uWS::OpCode opCode) {
    // "42" at the start of the message means there's a websocket message event.
    // The 4 signifies a websocket message
    // The 2 signifies a websocket event
    if (length && length > 2 && data[0] == '4' && data[1] == '2')
    {
      auto s = hasData(std::string(data).substr(0, length));
      if (s != "") {
        auto j = json::parse(s);
        std::string event = j[0].get<std::string>();
        if (event == "telemetry") {
          // j[1] is the data JSON object
          double cte = std::stod(j[1]["cte"].get<std::string>());
          double speed = std::stod(j[1]["speed"].get<std::string>());
          double angle = std::stod(j[1]["steering_angle"].get<std::string>());
          double steer_value;
          /*
          * TODO: Calcuate steering value here, remember the steering value is
          * [-1, 1].
          * NOTE: Feel free to play around with the throttle and speed. Maybe use
          * another PID controller to control the speed!
          */
          
          //steer_value = Kp * p_error + Ki * i_error + Kd * d_error ;//following the Q+A video
          pid.UpdateError(cte) ;
          steer_value = pid.TotalError() ;
          
          // DEBUG
          std::cout << "CTE: " << cte << " Steering Value: " << steer_value << std::endl;

          json msgJson;
          msgJson["steering_angle"] = steer_value;
          msgJson["throttle"] = 0.30; // adjusting this from 0.3 ,0.35, 0.5,0.4 all touched kerb a little back to default
          auto msg = "42[\"steer\"," + msgJson.dump() + "]";
          std::cout << msg << std::endl;
          ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
        }
      } else {
        // Manual driving
        std::string msg = "42[\"manual\",{}]";
        ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
      }
    }
  });

  // We don't need this since we're not using HTTP but if it's removed the program
  // doesn't compile :-(
  h.onHttpRequest([](uWS::HttpResponse *res, uWS::HttpRequest req, char *data, size_t, size_t) {
    const std::string s = "<h1>Hello world!</h1>";
    if (req.getUrl().valueLength == 1)
    {
      res->end(s.data(), s.length());
    }
    else
    {
      // i guess this should be done more gracefully?
      res->end(nullptr, 0);
    }
  });

  h.onConnection([&h](uWS::WebSocket<uWS::SERVER> ws, uWS::HttpRequest req) {
    std::cout << "Connected!!!" << std::endl;
  });

  h.onDisconnection([&h](uWS::WebSocket<uWS::SERVER> ws, int code, char *message, size_t length) {
    ws.close();
    std::cout << "Disconnected" << std::endl;
  });

  int port = 4567;
  if (h.listen(port))
  {
    std::cout << "Listening to port " << port << std::endl;
  }
  else
  {
    std::cerr << "Failed to listen to port" << std::endl;
    return -1;
  }
  h.run();
}
