#ifndef _SENSOR_DATA_H
#define _SENSOR_DATA_H

const char* SENSORDATA = 
"<!DOCTYPE html>\
<html lang=\"en\">\
<head>\
    <meta charset=\"UTF-8\">\
    <title>DALMAST Diagnostic Page</title>\
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\
    <style>\
        body {\
            width: 100%;\
            height: 100vh;\
            margin: 0;\
            font-family: Tahoma;\
            font-size: 16px;\
            color: #333;\
            background-color: #f5f5f5;\
        }\
        .site-header {\
            position: relative;\
            background-color: #ffffff;\
            padding: 0.01px 0;\
            box-shadow: 0 2px 5px rgba(0, 0, 0, 0.2);\
        }\
        .site-header__wrapper {\
            display: flex;\
            justify-content: space-between;\
            align-items: center;\
            padding: 10px;\
            height: 80px;\
        }\
        .brand {\
            color: #ff6600;\
            font-weight: bold;\
            font-size: 24px;\
            margin-right: 10px;\
            padding: 10px;\
        }\
        .nav {\
            display: flex;\
            align-items: center;\
        }\
        .nav__toggle {\
            display: none;\
        }\
        .nav__wrapper {\
            list-style: none;\
            display: flex;\
            max-width: 600px;\
        }\
        .nav__item {\
            margin-right: 20px;\
            padding: 10px;\
        }\
        .nav__item a {\
            text-decoration: none;\
            color: #ff6600;\
            font-weight: bold;\
            font-size: 24px;\
        }\
        .nav__item:last-child {\
            margin-right: 0;\
        }\
        @media (max-width: 599px) {\
            .nav {\
                flex-direction: column;\
            }\
            .nav__toggle {\
                display: block;\
                position: absolute;\
                right: 1rem;\
                top: 1rem;\
                cursor: pointer;\
                background-color: #ff6600;\
                color: white;\
                padding: 10px;\
                border-radius: 5px;\
            }\
            .nav__wrapper {\
                position: absolute;\
                top: 80px;\
                right: 0;\
                left: 0;\
                z-index: -1;\
                background-color: #ff6600;\
                visibility: hidden;\
                opacity: 0;\
                transform: translateY(-100%);\
                transition: transform 0.3s ease-out, opacity 0.3s ease-out;\
                flex-direction: column;\
                width: 100%;\
                padding: 10px 0;\
                box-shadow: 0 2px 5px rgba(0, 0, 0, 0.2);\
            }\
            .nav__wrapper.active {\
                visibility: visible;\
                opacity: 1;\
                transform: translateY(0);\
            }\
            .nav__item {\
                margin: 0;\
                padding: 10px 0;\
                text-align: center;\
            }\
            .nav__item a {\
                font-size: 24px;\
                color: white;\
            }\
            .nav__toggle.active+.nav__wrapper {\
                visibility: visible;\
                opacity: 1;\
                transform: translateY(0);\
                z-index: 1;\
            }\
            .nav__toggle.active {\
                z-index: 2;\
            }\
        }\
        h1,\
        h2 {\
            text-align: center;\
        }\
        h2 {\
            display: flex;\
            flex-direction: column;\
            margin: 20px 0;\
        }\
        .sensor-data-container {\
            padding: 20px;\
        }\
        .sensor-data {\
            display: flex;\
            flex-wrap: wrap;\
            justify-content: space-around;\
            margin: 20px 0;\
        }\
        .sensor-parameter {\
            flex: 1;\
            min-width: 300px;\
            margin: 0 10px 20px;\
            box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);\
            border-radius: 10px;\
            overflow: hidden;\
            background-color: #fff;\
            padding-bottom: 20px; \
        }\
        .sensor-parameter fieldset {\
            padding: 20px;\
            background-color: #fff;\
        }\
        .sensor-parameter h3 {\
            font-size: 24px;\
            font-weight: bold;\
            margin-bottom: 10px;\
            text-align: center;\
            color: #333;\
        }\
        .sensor-parameter p {\
            font-size: 18px;\
            margin: 0;\
            font-weight: bold;\
            text-align: center;\
            color: #555;\
        }\
        @media (max-width: 768px) {\
            .sensor-parameter {\
                flex: 1 0 100%;\
            }\
        }\
        @media (max-width: 599px) {\
            .site-header {\
                height: auto;\
                padding: 10px 0;\
            }\
            .site-header__wrapper {\
                flex-direction: column;\
            }\
            .nav {\
                margin-top: 10px;\
            }\
            .nav__toggle {\
                display: block;\
                margin-bottom: 10px;\
            }\
            .sensor-parameter {\
                min-width: auto;\
            }\
        }\
    </style>\
</head>\
<body>\
    <header class=\"site-header\">\
        <div class=\"site-header__wrapper\">\
            <p class=\"brand\">DalMast</p>\
            <nav class=\"nav\">\
                <div class=\"nav__toggle\">MENU</div>\
                <ul class=\"nav__wrapper\">\
                    <li class=\"nav__item\"><a href=\"/sensorData\">SENSOR</a></li>\
                    <li class=\"nav__item\"><a href=\"/controlData\">CONTROL</a></li>\
                    <li class=\"nav__item\"><a href=\"/navigationData\">NAVIGATION</a></li>\
                </ul>\
            </nav>\
        </div>\
    </header>\
    <script>\
        const navToggle = document.querySelector('.nav__toggle');\
        const navWrapper = document.querySelector('.nav__wrapper');\\
        navToggle.addEventListener('click', () => {\
            navToggle.classList.toggle('active');\
            navWrapper.classList.toggle('active');\
        });\
    </script>\
    <h2>Sensor Data</h2>\
    <div class=\"sensor-data-container\">\
        <div class=\"sensor-data\">\
            <div class=\"sensor-parameter\">\
                <h3>GPS</h3>\
                <p>Latitude: <span id=\"latitude\">-</span></p>\
                <p>Longitude: <span id=\"longitude\">-</span></p>\
            </div>\
            <div class=\"sensor-parameter\">\
                <h3>Wind Vane</h3>\
                <p>Wind Speed: <span id=\"wind_speed\">-</span></p>\
                <p>Wind Direction: <span id=\"wind_direction\">-</span></p>\
            </div>\
        </div>\
        <div class=\"sensor-data\">\
            <div class=\"sensor-parameter\">\
                <h3>Compass</h3>\
                <p>Compass Reading Type: <span id=\"comp_reading\">-</span></p>\
                <p>Yaw: <span id=\"yaw\">-</span></p>\
                <p>Pitch: <span id=\"pitch\">-</span></p>\
                <p>Row: <span id=\"row\">-</span></p>\
            </div>\
            <div class=\"sensor-parameter\">\
                <h3>Angular Sensor</h3>\
                <p>Angle: <span id=\"angel\">-</span></p>\
            </div>\
        </div>\
    </div>\
    <script>\
        var Socket;\
        function init() {\
            Socket = new WebSocket('ws://' + window.location.hostname + ':81/');\
            Socket.onmessage = function (event) {\
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
            console.log(obj.latitude);\
            console.log(obj.longitude);\
            console.log(obj.wind - direction);\
            console.log(obj.wind - speed);\
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
        window.onload = function (event) {\
            init();\
        }\
    </script>\
</body>\
</html>";

#endif
