#ifndef _WEBSITE_H
#define _WEBSITE_H

#define WEBSITE "<!DOCTYPE html>\
                    <html>\
                    <head>\
                    <meta charset='utf-8'>\
                    <meta name='viewport' content='width=device-width, initial-scale=1'>\
                    <title>DALMAST Diagnostic Page</title>\
                    <link rel='stylesheet' type='text/css'>\
                    <style>\
                    body{\
                        width: 100%;\
                        height: 100vh;\
                        margin: 0;\
                        font-family: Tahoma;\
                        font-size: 16px;\
                    }\
                    h1, h2{\
                        text-align: center;\
                    }\
                    h2{\
                        display: flex;\
                        flex-direction: column;\
                    }\
                    .round{\
                    border-radius: 15px;\
                    width:60%;\
                    display: block;\
                    margin: 10px 10px 10px 120px;\
                    }\
                    .left{\
                    width:50%;\
                    float: left;\
                    height: 100vh;\
                    }\
                    .border{\
                    border: 1px solid black;\
                    width:70%;\
                    float:right;\
                    }\
                    h3{\
                    text-align:center;\
                    }\
                    .right-top{\
                    width:45%;\
                    float: right;\
                    height: 35vh;\
                    }\
                    .right-bottom{\
                    width:45%;\
                    float: right;\
                    height: 60vh;\
                    }\
                    .last{\
                    height: 100vh;\
                    }\
                    </style>\
                    </head>\
                    <body>\
                    <fieldset>\
                    <h1>DALMAST Diagnostic Page</h1>\
                    <fieldset class='left' >\
                    <h2>Sensor Data</h2>\
                    <fieldset class='round'>\
                    <h3>GPS</h3>\
                    <p>Latitude: <span id='latitude'>-</span></p>\
                    <p>Longitude: <span id='longitude'>-</span></p>\
                    </fieldset>\
                    <fieldset class='round'>\
                    <h3>Wind Vane</h3>\
                    <p>Wind Speed: <span id='wind_speed'>-</span></p>\
                    <p>Wind Direction: <span id='wind_direction'>-</span></p>\
                    </fieldset>\
                    <fieldset class='round'>\
                    <h3>Compass</h3>\
                    <p>Compass Reading Type:<span id='comp_reading'>-</span></p>\
                    <p>Yaw: <span id='yaw'>-</span></p>\
                    <p>Pitch: <span id='pitch'>-</span></p>\
                    <p>Row: <span id='row'>-</span></p>\
                    </fieldset>\
                    <fieldset class='round'>\
                    <h3>Angular Sensor</h3>\
                    <p>Angle: <span id='angel'>-</span></p>\
                    </fieldset>\
                    </fieldset>\
                    <fieldset class='right-top'>\
                    <h2>Control Data</h2>\
                    <fieldset class='round'>\
                    <form action='/get'>\
                    Rudder[5,295]: <input type='text' name='rudder'><br>\
                    Sail[25,115]: <input type='text' name='sail'><br>\
                    <input type='submit' value='Submit'>\
                    </form>\
                    </fieldset>\
                    </fieldset>\
                    <fieldset class='right-bottom'>\
                    <h2>Nav Data</h2>\
                    <fieldset class='round'>\
                    <h3>Current Waypoint</h3>\
                    <p>Latitude: <span id='lat'>-</span></p>\
                    <p>Longitude: <span id='lon'>-</p>\
                    <p>Radius: <span id='rad'>-</span></p>\
                    <p>Distance: <span id='distance'>-</span></p>\
                    <p>Bearing: <span id='bearing'>-</span></p>\
                    <p>Course: <span id='course'>-</span></p>\
                    <p>Rudder angle: <span id='rudder_angle'>-</span></p>\
                    <p>Sail angle: <span id='sail_angle'>-</span></p>\
                    </fieldset>\
                    </fieldset>\
                    </body>\
                    <script>\
                    var Socket;\
                    function init() {\
                        Socket = new WebSocket('ws://' + window.location.hostname + ':81/');\
                        Socket.onmessage = function(event) {\
                        processCommand(event);\
                        };\
                    }\
                    function processCommand(event) {\
                        var obj = JSON.parse(event.data);\
                        document.getElementById('latitude').innerHTML = obj.latitude;\
                        document.getElementById('longitude').innerHTML = obj.longitude;\
                        document.getElementById('wind_direction').innerHTML = obj.wind_direction;\
                        document.getElementById('wind_speed').innerHTML = obj.wind_speed;\
                        document.getElementById('comp_reading').innerHTML = obj.comp_reading;\
                        document.getElementById('yaw').innerHTML = obj.yaw;\
                        document.getElementById('pitch').innerHTML = obj.pitch;\
                        document.getElementById('row').innerHTML = obj.row;\
                        document.getElementById('lat').innerHTML = obj.lat;\
                        document.getElementById('lon').innerHTML = obj.lon;\
                        document.getElementById('rad').innerHTML = obj.rad;\
                        document.getElementById('distance').innerHTML = obj.distance;\
                        document.getElementById('bearing').innerHTML = obj.bearing;\
                        document.getElementById('course').innerHTML = obj.course;\
                        document.getElementById('rudder_angle').innerHTML = obj.rudder_angle;\
                        document.getElementById('sail_angle').innerHTML = obj.sail_angle;\
                        console.log(obj.latitude);\
                        console.log(obj.longitude);\
                        console.log(obj.wind-direction);\
                        console.log(obj.wind-speed);\
                        console.log(obj.comp_reading);\
                        console.log(obj.yaw);\
                        console.log(obj.pitch);\
                        console.log(obj.row);\
                        console.log(obj.lat);\
                        console.log(obj.lon);\
                        console.log(obj.rad);\
                        console.log(obj.distance);\
                        console.log(obj.bearing);\
                        console.log(obj.course);\
                        console.log(obj.rudder_angle);\
                        console.log(obj.sail_angle);\
                    }\
                    window.onload = function(event) {\
                        init();\
                    }\
                    </script>\
                    </html>"

#endif