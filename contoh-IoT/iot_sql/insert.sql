insert into mylogin (
 name,
 password
) values (
 "admin",
 "digiorchid"
);


insert into room_type (
 type_id,
 name
) values (
 1,
 "standard"
);

insert into room_type (
 type_id,
 name
) values (
 2,
 "deluxe"
);



insert into iot_machine (
 iot_id,
 iot_name,
 iot_type,
 max_limit,
 min_limit
) values (
 "001",
 "DGI Thermo",
  1,
  27.0,
  15.0
);

insert into iot_machine (
 iot_id,
 iot_name,
 iot_type,
 max_limit,
 min_limit
) values (
 "002",
 "DGI Bright",
  2,
  1000.0,
  10.0
);

insert into iot_machine (
 iot_id,
 iot_name,
 iot_type,
 max_limit,
 min_limit
) values (
 "003",
 "DGI Switch",
  3,
  0.0,
  0.0
);


insert into monitor_alert (
 monitor_id,
 need_notif,
 email_server_ip,
 email_server_port,
 email_password,
 email_sender,
 email_receiver,
 email_message
) values (
  1,
  0,
 "123.123.xxx.xxx",
 "587",
 "mypass",
  "mymail@abcdef.com",
  "hariscom@mail.address.id",
  "DGI IoT Alert!"
);


