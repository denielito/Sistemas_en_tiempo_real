idf_component_register(SRCS "NTC.c" "motor.c" "uart.c" "main.c" "http_server.c" "wifi_app.c" "sensor.c"
                    INCLUDE_DIRS "."
                    EMBED_FILES webpage/app.css webpage/app.js webpage/favicon.ico webpage/index.html webpage/jquery-3.3.1.min.js)
