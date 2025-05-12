
-- Insert users (password: '123')
INSERT INTO Users (username, password_hash, role, full_name, email)
VALUES ('admin1', 'a665a45920422f9d417e4867efdc4fb8a04a1f3fff1fa07e998e86f7f7a27ae3', 'Admin', 'Admin User', 'admin@club.org');

INSERT INTO Users (username, password_hash, role, full_name, email)
VALUES ('student1', 'a665a45920422f9d417e4867efdc4fb8a04a1f3fff1fa07e998e86f7f7a27ae3', 'Student', 'Student One', 'student1@club.org');

-- Insert clubs
INSERT INTO Clubs (club_name, description)
VALUES ('Tech Club', 'Club for technology enthusiasts');

INSERT INTO Clubs (club_name, description)
VALUES ('Music Club', 'Club for music lovers');

-- Insert events
INSERT INTO Events (event_name, description, organizer_id, event_date, event_time, venue, club_id, max_capacity, event_status)
VALUES ('Tech Talk', 'Talk on AI', 1, TO_DATE('2025-05-01', 'YYYY-MM-DD'), '14:00', 'Room 101', 1, 50, 'Scheduled');

INSERT INTO Events (event_name, description, organizer_id, event_date, event_time, venue, club_id, max_capacity, event_status)
VALUES ('Music Fest', 'Live music event', 1, TO_DATE('2025-06-01', 'YYYY-MM-DD'), '18:00', 'Auditorium', 2, 100, 'Pending');

-- Insert registrations
INSERT INTO EventRegistrations (event_id, user_id, feedback)
VALUES (1, 2, 'Great event!');

-- Insert notifications
INSERT INTO Notifications (recipient_id, message)
VALUES (2, 'Your registration for Tech Talk is confirmed.');

-- Insert reports
INSERT INTO Reports (event_id, total_participants, average_feedback_score)
VALUES (1, 30, 4.5);

COMMIT;
