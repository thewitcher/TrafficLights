DROP TABLE IF EXISTS Experiment;
DROP TABLE IF EXISTS Junction;
DROP TABLE IF EXISTS Subcycle;
DROP TABLE IF EXISTS Statistic;

﻿CREATE TABLE Junction
(
    junctionId           integer primary key,
    junctionType      text
);

CREATE TABLE Statistic
(
    statisticId                 integer primary key,
    junctionId                 integer NOT NULL, 
    experimentId            integer NOT NULL,
    statisticTime            integer NOT NULL,
    vehicleCount            integer,
    vehicleWaitingTime integer,

    CONSTRAINT ExperimentFK FOREIGN KEY( experimentId ) REFERENCES Experiment( experimentId )
    CONSTRAINT JunctionFK FOREIGN KEY( junctionId ) REFERENCES Junction( junctionId )
);

CREATE TABLE Subcycle
(
    subcycleId           integer primary key,
    statisticId          integer NOT NULL,
    subcycleType         integer NOT NULL,
    vehicleCount         integer,
    vehicleWaitingTime   integer,

    CONSTRAINT StatisticFK FOREIGN KEY( statisticId ) REFERENCES Statistic( statisticId )
);

CREATE TABLE Experiment
(
    experimentId            integer primary key,
    experimentDate       text
);

﻿/* Add junctions */ 
/* Simple junction with id: 0 */ 
INSERT INTO Junction( junctionType ) VALUES( 'SimpleJunction' );
/* Simple junction with id: 1 */
INSERT INTO Junction( junctionType ) VALUES( 'SimpleJunction' );
/* Simple junction with id: 2 */
INSERT INTO Junction( junctionType ) VALUES( 'BladzioJunction' );
/* Simple junction with id: 3 */
INSERT INTO Junction( junctionType ) VALUES( 'SimpleJunction' );
/* Simple junction with id: 4 */
INSERT INTO Junction( junctionType ) VALUES( 'SimpleJunction' );
/* Simple junction with id: 5 */
INSERT INTO Junction( junctionType ) VALUES( 'SimpleJunction' );
/* Simple junction with id: 6 */
INSERT INTO Junction( junctionType ) VALUES( 'SimpleJunction' );

SELECT * FROM Junction;
SELECT * FROM Experiment;
SELECT * FROM Statistic;
SELECT * FROM Subcycle;

SELECT statisticTime, vehicleCount, vehicleWaitingTime FROM Statistic WHERE junctionId = 6 AND experimentId = 52;
SELECT statisticTime, vehicleCount, junctionId FROM Statistic WHERE experimentId = 52 ORDER BY statisticTime;

SELECT statisticTime, Subcycle.vehicleCount, subcycleType FROM Subcycle, Statistic WHERE  Statistic.statisticId = Subcycle.subcycleId AND junctionId = 0 ORDER BY statisticTime;

SELECT MAX( experimentId ) FROM Experiment;

INSERT INTO Experiment( experimentDate ) VALUES( '13 maja 2012' );