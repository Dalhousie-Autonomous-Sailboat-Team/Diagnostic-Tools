#ifndef _CONTROL_DATA_H
#define _CONTROL_DATA_H

const char* CONTROLDATA = 
"<!DOCTYPE html>\
<html lang=\"en\">\
<head>\
    <meta charset=\"UTF-8\" />\
    <title>DALMast</title>\
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" />\
    <style>\
        .site-header {\
            position: relative;\
            background-color: #ffffff;\
            padding: 0.01px 0;\
            box-shadow: 0 2px 5px rgba(0, 0, 0, 0.2);\
        }\
        body {\
            margin: 0;\
            padding: 0;\
            font-family: Tahoma;\
            width: 100%;\
            height: 100vh;\
            margin: 0;\
            font-size: 16px;\
            color: #333;\
            background-color: #f5f5f5;\
        }\
        .site-header__wrapper {\
            display: flex;\
            justify-content: space-between;\
            align-items: center;\
            padding: 10px;\
            height: 80px; \
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
                background-color: #ff6600; \
                color: white; \
                padding: 10px;\
                border-radius: 5px;\
            }\
            .nav__wrapper {\
                position: absolute;\
                top: 80px;\
                right: 0;\
                left: 0;\
                z-index: -1;\
                background-color: #ff6600; \
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
            .nav__toggle.active + .nav__wrapper {\
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
            margin: 20px;\
            padding: 10px;\
        }\
        .form-heading {\
            font-size: 24px;\
            font-weight: bold;\
            margin-bottom: 10px;\
            text-align: center;\
        }\
        .form-field {\
            border: 2px solid #ff6600;\
            padding: 10px;\
            font-size: 20px;\
            width: 100%;\
            margin: 5px 0;\
            box-shadow: 0 2px 5px rgba(0, 0, 0, 0.1);\
        }\
        .submit-button {\
            background-color: #ff6600;\
            color: white;\
            border: none;\
            padding: 10px 20px;\
            font-weight: bold;\
            font-size: 24px;\
            cursor: pointer;\
            margin-top: 10px;\
            box-shadow: 0 2px 5px rgba(0, 0, 0, 0.1);\
        }\
        .nav-data-button {\
            background-color: white;\
            color: #ff6600;\
            border: 2px solid #ff6600;\
            padding: 10px 20px;\
            font-weight: bold;\
            font-size: 24px;\
            cursor: pointer;\
            box-shadow: 0 2px 5px rgba(0, 0, 0, 0.1);\
        }\
    </style>\
</head>\
<body>\
<header class=\"site-header\">\
    <div class=\"wrapper site-header__wrapper\">\
        <p class=\"brand\">DalMast</p>\
        <nav class=\"nav\">\
            <div class=\"nav__toggle\">MENU</div> <!-- Added a menu toggle button for mobile -->\
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
        <p class=\"form-heading\">CONTROL DATA</p>\
        <br>\
        <br>\
        <input type=\"text\" name=\"rudder\" class=\"form-field\" placeholder=\"Rudder [70, 240]\">\
        <input type=\"text\" name=\"sail\" class=\"form-field\" placeholder=\"Sail [5, 140]\">\
        <button type=\"submit\" class=\"submit-button\">Submit</button>\
        <button class=\"nav-data-button\">Nav Data</button>\
    </form>\
</div>\
</body>\
</html>";

#endif
