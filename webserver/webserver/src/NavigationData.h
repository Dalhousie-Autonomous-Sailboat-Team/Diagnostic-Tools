#ifndef _NAVIGATION_DATA_H
#define _NAVIGATION_DATA_H

const char* NAVIGATIONDATA = 
"<!DOCTYPE html>\
<html lang=\"en\">\
<head>\
    <meta charset=\"UTF-8\" />\
    <title>DALMast</title>\
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" />\
    <style>\
        body {\
            margin: 0;\
            padding: 0;\
            font-family: Tahoma, sans-serif;\
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
        .form-container {\
            display: flex;\
            flex-direction: column;\
            align-items: center;\
            margin: 2rem auto;\
            max-width: 800px;\
            text-align: center;\
            padding: 2rem;\
            background-color: #f9f9f9;\
            box-shadow: 0 2px 5px rgba(0, 0, 0, 0.1);\
        }\
        .form-heading {\
            font-size: 28px;\
            font-weight: bold;\
            margin-bottom: 1.5rem;\
            color: #333;\
        }\
        .current-waypoint {\
            margin-top: 1.5rem;\
            font-size: 20px;\
            font-weight: bold;\
            text-align: center;\
            color: #333;\
        }\
        .current-waypoint p {\
            margin-bottom: 0.5rem;\
        }\
        .current-waypoint span {\
            font-size: 18px;\
            font-weight: normal;\
            color: #555;\
        }\
        .navigation-parameters {\
            display: flex;\
            flex-wrap: wrap;\
            justify-content: space-around;\
            margin-top: 2rem;\
        }\
        .parameter {\
            flex: 1;\
            min-width: 48%;\
            margin-bottom: 1rem;\
            background-color: white;\
            box-shadow: 0 2px 5px rgba(0, 0, 0, 0.1);\
            border-radius: 8px;\
            padding: 1.5rem;\
            box-sizing: border-box;\
        }\
        .parameter h3 {\
            font-size: 24px;\
            font-weight: bold;\
            margin-bottom: 0.5rem;\
            text-align: center;\
        }\
        .parameter p {\
            font-size: 18px;\
            margin: 0;\
            font-weight: bold;\
            text-align: center;\
        }\
        .submit-button,\
        .nav-data-button {\
            background-color: #ff6600;\
            color: white;\
            border: none;\
            padding: 10px 20px;\
            font-weight: bold;\
            font-size: 24px;\
            cursor: pointer;\
            margin-top: 2rem;\
            box-shadow: 0 2px 5px rgba(0, 0, 0, 0.1);\
            border-radius: 8px;\
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
        const navWrapper = document.querySelector('.nav__wrapper');\
        navToggle.addEventListener('click', () => {\
            navToggle.classList.toggle('active');\
            navWrapper.classList.toggle('active');\
        });\
    </script>\
    <div class=\"form-container\">\
        <form action=\"/get\">\
            <p class=\"form-heading\">NAVIGATION DATA</p>\
            <p class=\"current-waypoint\">Current Waypoint<span></span></p>\
            <div class=\"navigation-parameters\">\
                <div class=\"parameter\">\
                    <h3>Latitude</h3>\
                    <p><span id='lat'>-</span></p>\
                </div>\
                <div class=\"parameter\">\
                    <h3>Longitude</h3>\
                    <p><span id='lon'>-</span></p>\
                </div>\
                <div class=\"parameter\">\
                    <h3>Radius</h3>\
                    <p><span id='rad'>-</span></p>\
                </div>\
                <div class=\"parameter\">\
                    <h3>Distance</h3>\
                    <p><span id='distance'>-</span></p>\
                </div>\
                <div class=\"parameter\">\
                    <h3>Bearing</h3>\
                    <p><span id='bearing'>-</span></p>\
                </div>\
                <div class=\"parameter\">\
                    <h3>Course</h3>\
                    <p><span id='course'>-</span></p>\
                </div>\
                <div class=\"parameter\">\
                    <h3>Rudder angle</h3>\
                    <p><span id='rudder_angle'>-</span></p>\
                </div>\
                <div class=\"parameter\">\
                    <h3>Sail angle</h3>\
                    <p><span id='sail_angle'>-</span></p>\
                </div>\
            </div>\
            <button class=\"nav-data-button\">Control Data</button>\
        </form>\
    </div>\
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
                        document.getElementById('lat').innerHTML = obj.lat;\\
                        document.getElementById('lon').innerHTML = obj.lon;\
                        document.getElementById('rad').innerHTML = obj.rad;\
                        document.getElementById('distance').innerHTML = obj.distance;\
                        document.getElementById('bearing').innerHTML = obj.bearing;\
                        document.getElementById('course').innerHTML = obj.course;\
                        document.getElementById('rudder_angle').innerHTML = obj.rudder_angle;\
                        document.getElementById('sail_angle').innerHTML = obj.sail_angle;\
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
</html>";
#endif
