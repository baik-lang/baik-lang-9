CREATE TABLE smart_room (
 room_id    MEDIUMINT NOT NULL AUTO_INCREMENT,
 room       VARCHAR(32) NOT NULL,
 type       SMALLINT,
 isIot1     SMALLINT NOT NULL,
 iot1_ip    VARCHAR(20),
 isIot2     SMALLINT NOT NULL,
 iot2_ip    VARCHAR(20),
 isIot3     SMALLINT NOT NULL,
 iot3_ip    VARCHAR(20),
 isOccupied SMALLINT NOT NULL,
 PRIMARY KEY(room_id)
);

CREATE TABLE room_type (
 type_id    SMALLINT NOT NULL,
 name       VARCHAR(32) NOT NULL,
 PRIMARY KEY(type_id)
);

CREATE TABLE mylogin (
 name       VARCHAR(32) NOT NULL,
 password   VARCHAR(32) NOT NULL,
 PRIMARY KEY(name)
);

CREATE TABLE iot_machine (
iot_id    VARCHAR(20) NOT NULL,
iot_name  VARCHAR(20) NOT NULL,
iot_type  SMALLINT NOT NULL,
max_limit DOUBLE,
min_limit DOUBLE,
iot_val1  DOUBLE,
iot_val2  DOUBLE,
iot_date  DATE,

 PRIMARY KEY(iot_id)
);

CREATE TABLE monitor_alert (
 monitor_id        SMALLINT,
 need_notif        SMALLINT,
 email_server_ip   VARCHAR(64),
 email_server_port VARCHAR(8),
 email_password    VARCHAR(512),
 email_sender      VARCHAR(128),
 email_receiver    VARCHAR(128),
 email_message     VARCHAR(256)
);


