idf_component_register(SRCS "main.c" "led.c" "boton.c" "termistor.c" "http_server.c" "wifi_app.c"
                    INCLUDE_DIRS "."
                    EMBED_FILES webpage/app.css webpage/app.js webpage/favicon.ico webpage/index.html webpage/jquery-3.3.1.min.js)
