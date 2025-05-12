
-- Drop existing tables
DROP TABLE EventRegistrations;
DROP TABLE Notifications;
DROP TABLE Reports;
DROP TABLE Events;
DROP TABLE Clubs;
DROP TABLE Users;

-- Create tables
CREATE TABLE Users (
    user_id NUMBER GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
    username VARCHAR2(50) UNIQUE NOT NULL,
    password_hash VARCHAR2(64) NOT NULL,
    role VARCHAR2(20) NOT NULL CHECK (role IN ('Student', 'Organizer', 'Admin', 'Teacher')),
    full_name VARCHAR2(100) NOT NULL,
    email VARCHAR2(100) UNIQUE NOT NULL
);

CREATE TABLE Clubs (
    club_id NUMBER GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
    club_name VARCHAR2(100) UNIQUE NOT NULL,
    description VARCHAR2(4000)
);

CREATE TABLE Events (
    event_id NUMBER GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
    event_name VARCHAR2(100) NOT NULL,
    description VARCHAR2(4000),
    organizer_id NUMBER NOT NULL,
    event_date DATE NOT NULL,
    event_time VARCHAR2(5) NOT NULL,
    venue VARCHAR2(100) NOT NULL,
    club_id NUMBER,
    max_capacity NUMBER NOT NULL,
    event_status VARCHAR2(20) NOT NULL CHECK (event_status IN ('Scheduled', 'Pending', 'Cancelled', 'Ongoing', 'Completed')),
    CONSTRAINT fk_events_organizer FOREIGN KEY (organizer_id) REFERENCES Users(user_id),
    CONSTRAINT fk_events_club FOREIGN KEY (club_id) REFERENCES Clubs(club_id)
);

CREATE TABLE EventRegistrations (
    registration_id NUMBER GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
    event_id NUMBER NOT NULL,
    user_id NUMBER NOT NULL,
    registered_at TIMESTAMP DEFAULT SYSTIMESTAMP NOT NULL,
    feedback VARCHAR2(4000),
    CONSTRAINT fk_reg_event FOREIGN KEY (event_id) REFERENCES Events(event_id),
    CONSTRAINT fk_reg_user FOREIGN KEY (user_id) REFERENCES Users(user_id)
);

CREATE TABLE Notifications (
    notification_id NUMBER GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
    recipient_id NUMBER NOT NULL,
    message VARCHAR2(4000) NOT NULL,
    sent_at TIMESTAMP DEFAULT SYSTIMESTAMP NOT NULL,
    is_read NUMBER(1) DEFAULT 0 NOT NULL,
    CONSTRAINT fk_notif_recipient FOREIGN KEY (recipient_id) REFERENCES Users(user_id)
);

CREATE TABLE Reports (
    report_id NUMBER GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
    event_id NUMBER NOT NULL,
    total_participants NUMBER NOT NULL,
    average_feedback_score NUMBER,
    CONSTRAINT fk_report_event FOREIGN KEY (event_id) REFERENCES Events(event_id)
);

commit;