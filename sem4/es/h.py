
import tkinter as tk
from tkinter import ttk, messagebox
import cx_Oracle
import hashlib
import os
from datetime import datetime
import traceback

# Database setup and management
class Database:
    def __init__(self, user="system", password="pass", dsn="localhost:1521/XE"):
        self.user = user
        self.password = password
        self.dsn = dsn
        self.conn = None
        self.cursor = None
        self.initialize_database()
        self.register_udfs()

    def initialize_database(self):
        try:
            self.conn = cx_Oracle.connect(user=self.user, password=self.password, dsn=self.dsn)
            self.cursor = self.conn.cursor()
            # Execute schema
            with open("schema_oracle.sql", "r") as schema_file:
                schema_sql = schema_file.read()
                for statement in schema_sql.split(';'):
                    if statement.strip():
                        try:
                            self.cursor.execute(statement)
                        except cx_Oracle.DatabaseError as e:
                            error_obj, = e.args
                            print(f"Schema statement skipped (possibly already exists): ORA-{error_obj.code}: {error_obj.message}")
            # Execute sample data
            with open("sample_oracle.sql", "r") as sample_file:
                sample_sql = sample_file.read()
                for statement in sample_sql.split(';'):
                    if statement.strip():
                        self.cursor.execute(statement)
            self.conn.commit()
        except cx_Oracle.DatabaseError as e:
            error_obj, = e.args
            messagebox.showerror("Error", f"Database initialization failed: ORA-{error_obj.code}: {error_obj.message}")
            raise
        except FileNotFoundError:
            messagebox.showerror("Error", "Database schema or sample files not found!")
            raise

    def register_udfs(self):
        # PL/SQL function for event status formatting
        plsql = """
        CREATE OR REPLACE FUNCTION format_event_status(status IN VARCHAR2) RETURN VARCHAR2 IS
        BEGIN
            CASE status
                WHEN 'Scheduled' THEN RETURN 'Approved: Scheduled';
                WHEN 'Pending' THEN RETURN 'Awaiting: Pending';
                WHEN 'Cancelled' THEN RETURN 'Rejected: Cancelled';
                WHEN 'Ongoing' THEN RETURN 'Active: Ongoing';
                WHEN 'Completed' THEN RETURN 'Finished: Completed';
                ELSE RETURN status;
            END CASE;
        END;
        """
        try:
            self.cursor.execute(plsql)
            self.conn.commit()
        except cx_Oracle.DatabaseError as e:
            error_obj, = e.args
            print(f"Error registering UDF: ORA-{error_obj.code}: {error_obj.message}")

    def hash_password(self, password):
        return hashlib.sha256(password.encode()).hexdigest()

    def authenticate_user(self, username, password):
        try:
            hashed_password = self.hash_password(password)
            self.cursor.execute(
                "SELECT user_id, role FROM Users WHERE username = :v1 AND password_hash = :v2",
                {'v1': username, 'v2': hashed_password}
            )
            return self.cursor.fetchone()
        except cx_Oracle.DatabaseError as e:
            error_obj, = e.args
            print(f"Authentication error: ORA-{error_obj.code}: {error_obj.message}")
            return None

    def reset_password(self, username, new_password):
        try:
            hashed_password = self.hash_password(new_password)
            self.cursor.execute(
                "UPDATE Users SET password_hash = :v1 WHERE username = :v2",
                {'v1': hashed_password, 'v2': username}
            )
            self.conn.commit()
            return self.cursor.rowcount > 0
        except cx_Oracle.DatabaseError as e:
            error_obj, = e.args
            print(f"Reset password error: ORA-{error_obj.code}: {error_obj.message}")
            return False

    def user_exists(self, username):
        try:
            self.cursor.execute("SELECT 1 FROM Users WHERE username = :v1", {'v1': username})
            return self.cursor.fetchone() is not None
        except cx_Oracle.DatabaseError as e:
            error_obj, = e.args
            print(f"User exists check error: ORA-{error_obj.code}: {error_obj.message}")
            return False

    def generate_user_activity_summary(self, user_id):
        try:
            summary = {'proposed_events': 0, 'registrations': 0, 'approved_events': 0}
            self.cursor.execute(
                "SELECT COUNT(*) FROM Events WHERE organizer_id = :v1",
                {'v1': user_id}
            )
            summary['proposed_events'] = self.cursor.fetchone()[0]
            self.cursor.execute(
                "SELECT COUNT(*) FROM EventRegistrations WHERE user_id = :v1",
                {'v1': user_id}
            )
            summary['registrations'] = self.cursor.fetchone()[0]
            self.cursor.execute(
                "SELECT COUNT(*) FROM Events WHERE organizer_id = :v1 AND event_status = 'Scheduled'",
                {'v1': user_id}
            )
            summary['approved_events'] = self.cursor.fetchone()[0]
            return summary
        except cx_Oracle.DatabaseError as e:
            error_obj, = e.args
            print(f"Error generating user activity summary: ORA-{error_obj.code}: {error_obj.message}")
            return None

    def __del__(self):
        if self.cursor:
            self.cursor.close()
        if self.conn:
            self.conn.close()

# Main Application
class ClubManagementApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Club Management System")
        self.root.geometry("1000x600")
        self.db = Database()
        self.current_user = None
        self.current_role = None
        
        # Style configuration
        self.style = ttk.Style()
        self.style.configure("TButton", padding=10, font=("Helvetica", 12), foreground="black", background="#4CAF50")
        self.style.configure("TLabel", font=("Helvetica", 12), foreground="#333333")
        self.style.configure("TEntry", font=("Helvetica", 12))
        self.style.configure("Custom.TFrame", background="#E0F7FA")
        self.style.map("TButton", background=[("active", "#45A049")], foreground=[("active", "black")])
        
        self.create_login_page()

    def clear_frame(self):
        for widget in self.root.winfo_children():
            widget.destroy()

    def validate_date(self, date_str):
        """Validate date format (YYYY-MM-DD)."""
        try:
            datetime.strptime(date_str, '%Y-%m-%d')
            return True
        except ValueError:
            return False

    def validate_time(self, time_str):
        """Validate time format (HH:MM)."""
        try:
            datetime.strptime(time_str, '%H:%M')
            return True
        except ValueError:
            return False

    def create_login_page(self):
        self.clear_frame()
        
        frame = ttk.Frame(self.root, padding="20", style="Custom.TFrame")
        frame.pack(expand=True)

        ttk.Label(frame, text="Club Management System", font=("Helvetica", 24, "bold"), foreground="#007BFF").grid(row=0, column=0, columnspan=2, pady=20)
        
        ttk.Label(frame, text="Username:").grid(row=1, column=0, pady=10, sticky="e")
        self.username_entry = ttk.Entry(frame)
        self.username_entry.grid(row=1, column=1, pady=10)
        
        ttk.Label(frame, text="Password:").grid(row=2, column=0, pady=10, sticky="e")
        self.password_entry = ttk.Entry(frame, show="*")
        self.password_entry.grid(row=2, column=1, pady=10)
        
        ttk.Button(frame, text="Login", command=self.handle_login).grid(row=3, column=0, columnspan=2, pady=10)
        ttk.Button(frame, text="Forgot Password?", command=self.create_forgot_password_page).grid(row=4, column=0, columnspan=2, pady=5)
        ttk.Button(frame, text="Register", command=self.create_register_page).grid(row=5, column=0, columnspan=2, pady=5)
        
        self.logout_button = ttk.Button(frame, text="Logout", command=self.handle_logout)
        self.logout_button.grid(row=6, column=0, columnspan=2, pady=5)
        self.update_logout_button_state()
        
        self.root.configure(bg="#E0F7FA")

    def update_logout_button_state(self):
        if self.current_user:
            self.logout_button.state(['!disabled'])
        else:
            self.logout_button.state(['disabled'])

    def handle_logout(self):
        self.current_user = None
        self.current_role = None
        self.create_login_page()
        messagebox.showinfo("Success", "Logged out successfully!")

    def create_forgot_password_page(self):
        self.clear_frame()
        
        frame = ttk.Frame(self.root, padding="20", style="Custom.TFrame")
        frame.pack(expand=True)

        ttk.Label(frame, text="Reset Password", font=("Helvetica", 24, "bold"), foreground="#007BFF").grid(row=0, column=0, columnspan=2, pady=20)
        
        ttk.Label(frame, text="Username:").grid(row=1, column=0, pady=10, sticky="e")
        username_entry = ttk.Entry(frame)
        username_entry.grid(row=1, column=1, pady=10)
        
        ttk.Label(frame, text="New Password:").grid(row=2, column=0, pady=10, sticky="e")
        new_password_entry = ttk.Entry(frame, show="*")
        new_password_entry.grid(row=2, column=1, pady=10)
        
        def reset_password():
            username = username_entry.get()
            new_password = new_password_entry.get()
            if not username or not new_password:
                messagebox.showerror("Error", "All fields are required!", parent=self.root)
                return
            if self.db.user_exists(username):
                if self.db.reset_password(username, new_password):
                    messagebox.showinfo("Success", "Password reset successfully!", parent=self.root)
                    self.create_login_page()
                else:
                    messagebox.showerror("Error", "Failed to reset password!", parent=self.root)
            else:
                messagebox.showerror("Error", "Username not found!", parent=self.root)
        
        ttk.Button(frame, text="Reset Password", command=reset_password).grid(row=3, column=0, columnspan=2, pady=10)
        ttk.Button(frame, text="Back to Login", command=self.create_login_page).grid(row=4, column=0, columnspan=2, pady=5)
        
        self.root.configure(bg="#E0F7FA")

    def create_register_page(self):
        self.clear_frame()
        
        frame = ttk.Frame(self.root, padding="20", style="Custom.TFrame")
        frame.pack(expand=True)

        ttk.Label(frame, text="Register New User", font=("Helvetica", 24, "bold"), foreground="#007BFF").grid(row=0, column=0, columnspan=2, pady=20)
        
        ttk.Label(frame, text="Username:").grid(row=1, column=0, pady=10, sticky="e")
        username_entry = ttk.Entry(frame)
        username_entry.grid(row=1, column=1, pady=10)
        
        ttk.Label(frame, text="Password:").grid(row=2, column=0, pady=10, sticky="e")
        password_entry = ttk.Entry(frame, show="*")
        password_entry.grid(row=2, column=1, pady=10)
        
        ttk.Label(frame, text="Full Name:").grid(row=3, column=0, pady=10, sticky="e")
        full_name_entry = ttk.Entry(frame)
        full_name_entry.grid(row=3, column=1, pady=10)
        
        ttk.Label(frame, text="Email:").grid(row=4, column=0, pady=10, sticky="e")
        email_entry = ttk.Entry(frame)
        email_entry.grid(row=4, column=1, pady=10)
        
        ttk.Label(frame, text="Role:").grid(row=5, column=0, pady=10, sticky="e")
        role_combo = ttk.Combobox(frame, values=["Student", "Organizer", "Admin", "Teacher"])
        role_combo.set("Student")
        role_combo.grid(row=5, column=1, pady=10)
        
        def register_user():
            username = username_entry.get()
            password = password_entry.get()
            full_name = full_name_entry.get()
            email = email_entry.get()
            role = role_combo.get()
            
            if not all([username, password, full_name, email, role]):
                messagebox.showerror("Error", "All fields are required!", parent=self.root)
                return
            
            if self.db.user_exists(username):
                messagebox.showerror("Error", "Username already exists!", parent=self.root)
                return
                
            try:
                hashed_password = self.db.hash_password(password)
                self.db.cursor.execute(
                    """INSERT INTO Users (username, password_hash, role, full_name, email)
                    VALUES (:v1, :v2, :v3, :v4, :v5)""",
                    {'v1': username, 'v2': hashed_password, 'v3': role, 'v4': full_name, 'v5': email}
                )
                self.db.conn.commit()
                messagebox.showinfo("Success", "User registered successfully!", parent=self.root)
                self.create_login_page()
            except cx_Oracle.DatabaseError as e:
                error_obj, = e.args
                messagebox.showerror("Error", f"Registration failed: ORA-{error_obj.code}: {error_obj.message}", parent=self.root)
        
        ttk.Button(frame, text="Register", command=register_user).grid(row=6, column=0, columnspan=2, pady=10)
        ttk.Button(frame, text="Back to Login", command=self.create_login_page).grid(row=7, column=0, columnspan=2, pady=5)
        
        self.root.configure(bg="#E0F7FA")

    def handle_login(self):
        username = self.username_entry.get()
        password = self.password_entry.get()
        
        user_data = self.db.authenticate_user(username, password)
        if user_data:
            self.current_user, self.current_role = user_data
            if self.current_role == "Admin":
                self.create_admin_dashboard()
            elif self.current_role == "Organizer":
                self.create_organizer_dashboard()
            elif self.current_role == "Teacher":
                self.create_teacher_dashboard()
            else:
                self.create_student_dashboard()
            self.update_logout_button_state()
        else:
            messagebox.showerror("Login Failed", "Invalid credentials!", parent=self.root)

    def create_admin_dashboard(self):
        self.clear_frame()
        
        notebook = ttk.Notebook(self.root)
        notebook.pack(pady=10, expand=True, fill="both")
        
        events_frame = ttk.Frame(notebook)
        notebook.add(events_frame, text="Events")
        self.create_events_management(events_frame)
        
        users_frame = ttk.Frame(notebook)
        notebook.add(users_frame, text="Users")
        self.create_users_management(users_frame)
        
        reports_frame = ttk.Frame(notebook)
        notebook.add(reports_frame, text="Reports")
        self.create_reports_management(reports_frame)
        
        approvals_frame = ttk.Frame(notebook)
        notebook.add(approvals_frame, text="Event Approvals")
        self.create_approvals_management(approvals_frame)
        
        stats_frame = ttk.Frame(notebook)
        notebook.add(stats_frame, text="Event Statistics")
        self.create_event_statistics(stats_frame)
        
        activity_frame = ttk.Frame(notebook)
        notebook.add(activity_frame, text="User Activity")
        self.create_user_activity(activity_frame)
        
        summary_frame = ttk.Frame(notebook)
        notebook.add(summary_frame, text="Event Summary")
        self.create_event_summary(summary_frame)
        
        ttk.Button(self.root, text="Logout", command=self.handle_logout).pack(pady=10)

    def create_organizer_dashboard(self):
        self.clear_frame()
        
        notebook = ttk.Notebook(self.root)
        notebook.pack(pady=10, expand=True, fill="both")
        
        events_frame = ttk.Frame(notebook)
        notebook.add(events_frame, text="My Events")
        self.create_events_management(events_frame, organizer=True)
        
        notifications_frame = ttk.Frame(notebook)
        notebook.add(notifications_frame, text="Notifications")
        self.create_notifications_management(notifications_frame)
        
        approvals_frame = ttk.Frame(notebook)
        notebook.add(approvals_frame, text="Event Approvals")
        self.create_approvals_management(approvals_frame)
        
        ttk.Button(self.root, text="Logout", command=self.handle_logout).pack(pady=10)

    def create_teacher_dashboard(self):
        self.clear_frame()
        
        notebook = ttk.Notebook(self.root)
        notebook.pack(pady=10, expand=True, fill="both")
        
        events_frame = ttk.Frame(notebook)
        notebook.add(events_frame, text="Events")
        self.create_events_management(events_frame, organizer=True)
        
        approvals_frame = ttk.Frame(notebook)
        notebook.add(approvals_frame, text="Event Approvals")
        self.create_approvals_management(approvals_frame)
        
        ttk.Button(self.root, text="Logout", command=self.handle_logout).pack(pady=10)

    def create_student_dashboard(self):
        self.clear_frame()
        
        notebook = ttk.Notebook(self.root)
        notebook.pack(pady=10, expand=True, fill="both")
        
        events_frame = ttk.Frame(notebook)
        notebook.add(events_frame, text="Events")
        self.create_student_events(events_frame)
        
        registrations_frame = ttk.Frame(notebook)
        notebook.add(registrations_frame, text="My Registrations")
        self.create_registrations_management(registrations_frame)
        
        propose_event_frame = ttk.Frame(notebook)
        notebook.add(propose_event_frame, text="Propose Event")
        self.create_propose_event(propose_event_frame)
        
        ttk.Button(self.root, text="Logout", command=self.handle_logout).pack(pady=10)

    def create_events_management(self, parent, organizer=False):
        frame = ttk.Frame(parent, padding="10")
        frame.pack(fill="both", expand=True)
        
        self.no_events_label = ttk.Label(frame, text="No scheduled events available.", font=("Helvetica", 12))
        self.no_events_label.pack(pady=10)
        
        tree = ttk.Treeview(frame, columns=("ID", "Name", "Date", "Time", "Venue", "Club", "Status"), show="headings")
        tree.heading("ID", text="ID")
        tree.heading("Name", text="Event Name")
        tree.heading("Date", text="Date")
        tree.heading("Time", text="Time")
        tree.heading("Venue", text="Venue")
        tree.heading("Club", text="Club")
        tree.heading("Status", text="Status")
        tree.pack(fill="both", expand=True)
        
        button_frame = ttk.Frame(frame)
        button_frame.pack(pady=10, fill="x")
        
        form_frame = ttk.Frame(frame)
        form_frame.pack(pady=10, fill="x")
        
        ttk.Label(form_frame, text="Event Name:").grid(row=0, column=0, padx=5)
        event_name = ttk.Entry(form_frame)
        event_name.grid(row=0, column=1, padx=5)
        
        ttk.Label(form_frame, text="Description:").grid(row=1, column=0, padx=5)
        description = ttk.Entry(form_frame)
        description.grid(row=1, column=1, padx=5)
        
        ttk.Label(form_frame, text="Date (YYYY-MM-DD):").grid(row=2, column=0, padx=5)
        event_date = ttk.Entry(form_frame)
        event_date.grid(row=2, column=1, padx=5)
        
        ttk.Label(form_frame, text="Time (HH:MM):").grid(row=3, column=0, padx=5)
        event_time = ttk.Entry(form_frame)
        event_time.grid(row=3, column=1, padx=5)
        
        ttk.Label(form_frame, text="Venue:").grid(row=4, column=0, padx=5)
        venue = ttk.Entry(form_frame)
        venue.grid(row=4, column=1, padx=5)
        
        ttk.Label(form_frame, text="Max Capacity:").grid(row=5, column=0, padx=5)
        max_capacity = ttk.Entry(form_frame)
        max_capacity.grid(row=5, column=1, padx=5)
        
        ttk.Label(form_frame, text="Club:").grid(row=6, column=0, padx=5)
        club_combo = ttk.Combobox(form_frame)
        club_combo.grid(row=6, column=1, padx=5)
        
        try:
            self.db.cursor.execute("SELECT club_name FROM Clubs")
            clubs = [row[0] for row in self.db.cursor.fetchall()]
            club_combo["values"] = clubs
            if clubs:
                club_combo.set(clubs[0])
        except cx_Oracle.DatabaseError as e:
            error_obj, = e.args
            messagebox.showerror("Error", f"Failed to load clubs: ORA-{error_obj.code}: {error_obj.message}", parent=parent)
        
        def add_event():
            try:
                if not all([event_name.get(), event_date.get(), event_time.get(), venue.get(), max_capacity.get(), club_combo.get()]):
                    messagebox.showerror("Error", "All fields are required!", parent=parent)
                    return
                
                self.db.cursor.execute("SELECT club_id FROM Clubs WHERE club_name = :v1", {'v1': club_combo.get()})
                club_id_result = self.db.cursor.fetchone()
                if not club_id_result:
                    messagebox.showerror("Error", "Please select a valid club!", parent=parent)
                    return
                club_id = club_id_result[0]
                
                try:
                    capacity = int(max_capacity.get())
                    if capacity <= 0:
                        raise ValueError("Capacity must be positive")
                except ValueError:
                    messagebox.showerror("Error", "Invalid max capacity!", parent=parent)
                    return
                
                if not self.validate_date(event_date.get()):
                    messagebox.showerror("Error", "Invalid date format (YYYY-MM-DD)!", parent=parent)
                    return
                if not self.validate_time(event_time.get()):
                    messagebox.showerror("Error", "Invalid time format (HH:MM)!", parent=parent)
                    return
                
                sql = """
                    INSERT INTO Events (event_name, description, organizer_id, event_date, event_time, venue, club_id, max_capacity, event_status)
                    VALUES (:v1, :v2, :v3, TO_DATE(:v4, 'YYYY-MM-DD'), :v5, :v6, :v7, :v8, :v9)
                """
                params = {
                    'v1': event_name.get(),
                    'v2': description.get(),
                    'v3': self.current_user,
                    'v4': event_date.get(),
                    'v5': event_time.get(),
                    'v6': venue.get(),
                    'v7': club_id,
                    'v8': capacity,
                    'v9': 'Scheduled'
                }
                print("Executing SQL:", sql)
                print("Parameters:", params)
                self.db.cursor.execute(sql, params)
                self.db.conn.commit()
                messagebox.showinfo("Success", "Event added successfully! Click 'Refresh Events' to view.", parent=parent)
                refresh_events()
            except cx_Oracle.DatabaseError as e:
                error_obj, = e.args
                messagebox.showerror("Error", f"Failed to add event: ORA-{error_obj.code}: {error_obj.message}", parent=parent)
                self.db.conn.rollback()
        
        ttk.Button(form_frame, text="Add Event", command=add_event).grid(row=7, column=0, columnspan=2, pady=10)
        
        def refresh_events():
            try:
                for item in tree.get_children():
                    tree.delete(item)
                query = """
                    SELECT e.event_id, e.event_name, TO_CHAR(e.event_date, 'YYYY-MM-DD'), e.event_time, e.venue, c.club_name, format_event_status(e.event_status)
                    FROM Events e
                    JOIN Clubs c ON e.club_id = c.club_id
                    WHERE e.event_status = :v1
                """
                params = {'v1': 'Scheduled'}
                if organizer:
                    query += " AND e.organizer_id = :v2"
                    params['v2'] = self.current_user
                print("Executing SQL:", query)
                print("Parameters:", params)
                self.db.cursor.execute(query, params)
                rows = self.db.cursor.fetchall()
                print(f"Events fetched: {rows}")
                for row in rows:
                    tree.insert("", "end", values=row)
                if rows:
                    self.no_events_label.pack_forget()
                else:
                    self.no_events_label.pack(pady=10)
            except cx_Oracle.DatabaseError as e:
                error_obj, = e.args
                messagebox.showerror("Error", f"Failed to refresh events: ORA-{error_obj.code}: {error_obj.message}", parent=parent)
        
        ttk.Button(button_frame, text="Refresh Events", command=refresh_events).pack(side="left", padx=5)
        refresh_events()

    def create_propose_event(self, parent):
        frame = ttk.Frame(parent, padding="10")
        frame.pack(fill="both", expand=True)
        
        form_frame = ttk.Frame(frame)
        form_frame.pack(pady=10, fill="x")
        
        ttk.Label(form_frame, text="Event Name:").grid(row=0, column=0, padx=5)
        event_name = ttk.Entry(form_frame)
        event_name.grid(row=0, column=1, padx=5)
        
        ttk.Label(form_frame, text="Description:").grid(row=1, column=0, padx=5)
        description = ttk.Entry(form_frame)
        description.grid(row=1, column=1, padx=5)
        
        ttk.Label(form_frame, text="Date (YYYY-MM-DD):").grid(row=2, column=0, padx=5)
        event_date = ttk.Entry(form_frame)
        event_date.grid(row=2, column=1, padx=5)
        
        ttk.Label(form_frame, text="Time (HH:MM):").grid(row=3, column=0, padx=5)
        event_time = ttk.Entry(form_frame)
        event_time.grid(row=3, column=1, padx=5)
        
        ttk.Label(form_frame, text="Venue:").grid(row=4, column=0, padx=5)
        venue = ttk.Entry(form_frame)
        venue.grid(row=4, column=1, padx=5)
        
        ttk.Label(form_frame, text="Max Capacity:").grid(row=5, column=0, padx=5)
        max_capacity = ttk.Entry(form_frame)
        max_capacity.grid(row=5, column=1, padx=5)
        
        ttk.Label(form_frame, text="Club:").grid(row=6, column=0, padx=5)
        club_combo = ttk.Combobox(form_frame)
        club_combo.grid(row=6, column=1, padx=5)
        
        try:
            self.db.cursor.execute("SELECT club_name FROM Clubs")
            clubs = [row[0] for row in self.db.cursor.fetchall()]
            club_combo["values"] = clubs
            if clubs:
                club_combo.set(clubs[0])
        except cx_Oracle.DatabaseError as e:
            error_obj, = e.args
            messagebox.showerror("Error", f"Failed to load clubs: ORA-{error_obj.code}: {error_obj.message}", parent=parent)
        
        def propose_event():
            try:
                if not all([event_name.get(), event_date.get(), event_time.get(), venue.get(), max_capacity.get(), club_combo.get()]):
                    messagebox.showerror("Error", "All fields are required!", parent=parent)
                    return
                
                self.db.cursor.execute("SELECT club_id FROM Clubs WHERE club_name = :v1", {'v1': club_combo.get()})
                club_id_result = self.db.cursor.fetchone()
                if not club_id_result:
                    messagebox.showerror("Error", "Please select a valid club!", parent=parent)
                    return
                club_id = club_id_result[0]
                
                try:
                    capacity = int(max_capacity.get())
                    if capacity <= 0:
                        raise ValueError("Capacity must be positive")
                except ValueError:
                    messagebox.showerror("Error", "Invalid max capacity!", parent=parent)
                    return
                
                if not self.validate_date(event_date.get()):
                    messagebox.showerror("Error", "Invalid date format (YYYY-MM-DD)!", parent=parent)
                    return
                if not self.validate_time(event_time.get()):
                    messagebox.showerror("Error", "Invalid time format (HH:MM)!", parent=parent)
                    return
                
                sql = """
                    INSERT INTO Events (event_name, description, organizer_id, event_date, event_time, venue, club_id, max_capacity, event_status)
                    VALUES (:v1, :v2, :v3, TO_DATE(:v4, 'YYYY-MM-DD'), :v5, :v6, :v7, :v8, :v9)
                """
                params = {
                    'v1': event_name.get(),
                    'v2': description.get(),
                    'v3': self.current_user,
                    'v4': event_date.get(),
                    'v5': event_time.get(),
                    'v6': venue.get(),
                    'v7': club_id,
                    'v8': capacity,
                    'v9': 'Pending'
                }
                print("Executing SQL:", sql)
                print("Parameters:", params)
                self.db.cursor.execute(sql, params)
                self.db.conn.commit()
                messagebox.showinfo("Success", "Event proposed! Awaiting approval.", parent=parent)
                event_name.delete(0, tk.END)
                description.delete(0, tk.END)
                event_date.delete(0, tk.END)
                event_time.delete(0, tk.END)
                venue.delete(0, tk.END)
                max_capacity.delete(0, tk.END)
                if clubs:
                    club_combo.set(clubs[0])
            except cx_Oracle.DatabaseError as e:
                error_obj, = e.args
                errmsg = f"Failed to propose event: ORA-{error_obj.code}: {error_obj.message}"
                print(f"--- ORACLE DB ERROR (propose_event) ---")
                print(errmsg)
                traceback.print_exc()
                print(f"--- END ORACLE DB ERROR ---")
                messagebox.showerror("DB Error", errmsg, parent=parent)
                self.db.conn.rollback()
        
        ttk.Button(form_frame, text="Propose Event", command=propose_event).grid(row=7, column=0, columnspan=2, pady=10)

    def create_approvals_management(self, parent):
        frame = ttk.Frame(parent, padding="10")
        frame.pack(fill="both", expand=True)
        
        self.no_events_label = ttk.Label(frame, text="No pending events to approve.", font=("Helvetica", 12))
        self.no_events_label.pack(pady=10)
        
        tree = ttk.Treeview(frame, columns=("ID", "Name", "Date", "Time", "Venue", "Club", "Status"), show="headings")
        tree.heading("ID", text="ID")
        tree.heading("Name", text="Event Name")
        tree.heading("Date", text="Date")
        tree.heading("Time", text="Time")
        tree.heading("Venue", text="Venue")
        tree.heading("Club", text="Club")
        tree.heading("Status", text="Status")
        tree.pack(fill="both", expand=True)
        
        button_frame = ttk.Frame(frame)
        button_frame.pack(pady=10, fill="x")
        
        def refresh_approvals():
            try:
                for item in tree.get_children():
                    tree.delete(item)
                sql = """
                    SELECT e.event_id, e.event_name, TO_CHAR(e.event_date, 'YYYY-MM-DD'), e.event_time, e.venue, c.club_name, format_event_status(e.event_status)
                    FROM Events e
                    JOIN Clubs c ON e.club_id = c.club_id
                    WHERE e.event_status = :v1
                """
                self.db.cursor.execute(sql, {'v1': 'Pending'})
                rows = self.db.cursor.fetchall()
                print(f"Pending events fetched: {rows}")
                for row in rows:
                    tree.insert("", "end", values=row)
                if rows:
                    self.no_events_label.pack_forget()
                else:
                    self.no_events_label.pack(pady=10)
            except cx_Oracle.DatabaseError as e:
                error_obj, = e.args
                messagebox.showerror("Error", f"Failed to refresh approvals: ORA-{error_obj.code}: {error_obj.message}", parent=parent)
        
        def approve_event():
            selected = tree.selection()
            if not selected:
                messagebox.showerror("Error", "Please select an event to approve!", parent=parent)
                return
            event_id = tree.item(selected)["values"][0]
            try:
                self.db.cursor.execute(
                    "UPDATE Events SET event_status = :v1 WHERE event_id = :v2",
                    {'v1': 'Scheduled', 'v2': event_id}
                )
                self.db.conn.commit()
                if self.db.cursor.rowcount == 0:
                    messagebox.showerror("Error", "No event updated. Check event ID.", parent=parent)
                    return
                messagebox.showinfo("Success", "Event approved! Click 'Refresh Events' in the Events tab to view.", parent=parent)
                refresh_approvals()
            except cx_Oracle.DatabaseError as e:
                error_obj, = e.args
                messagebox.showerror("Error", f"Approval failed: ORA-{error_obj.code}: {error_obj.message}", parent=parent)
        
        def reject_event():
            selected = tree.selection()
            if not selected:
                messagebox.showerror("Error", "Please select an event to reject!", parent=parent)
                return
            event_id = tree.item(selected)["values"][0]
            try:
                self.db.cursor.execute(
                    "UPDATE Events SET event_status = :v1 WHERE event_id = :v2",
                    {'v1': 'Cancelled', 'v2': event_id}
                )
                self.db.conn.commit()
                if self.db.cursor.rowcount == 0:
                    messagebox.showerror("Error", "No event updated. Check event ID.", parent=parent)
                    return
                messagebox.showinfo("Success", "Event rejected!", parent=parent)
                refresh_approvals()
            except cx_Oracle.DatabaseError as e:
                error_obj, = e.args
                messagebox.showerror("Error", f"Rejection failed: ORA-{error_obj.code}: {error_obj.message}", parent=parent)
        
        ttk.Button(button_frame, text="Approve Event", command=approve_event).pack(side="left", padx=5)
        ttk.Button(button_frame, text="Reject Event", command=reject_event).pack(side="left", padx=5)
        refresh_approvals()

    def create_users_management(self, parent):
        frame = ttk.Frame(parent, padding="10")
        frame.pack(fill="both", expand=True)
        
        tree = ttk.Treeview(frame, columns=("ID", "Username", "Role", "Email"), show="headings")
        tree.heading("ID", text="ID")
        tree.heading("Username", text="Username")
        tree.heading("Role", text="Role")
        tree.heading("Email", text="Email")
        tree.pack(fill="both", expand=True)
        
        def refresh_users():
            try:
                for item in tree.get_children():
                    tree.delete(item)
                self.db.cursor.execute("SELECT user_id, username, role, email FROM Users")
                for row in self.db.cursor.fetchall():
                    tree.insert("", "end", values=row)
            except cx_Oracle.DatabaseError as e:
                error_obj, = e.args
                messagebox.showerror("Error", f"Failed to refresh users: ORA-{error_obj.code}: {error_obj.message}", parent=parent)
        
        refresh_users()
        
        form_frame = ttk.Frame(frame)
        form_frame.pack(pady=10, fill="x")
        
        ttk.Label(form_frame, text="Username:").grid(row=0, column=0, padx=5)
        username = ttk.Entry(form_frame)
        username.grid(row=0, column=1, padx=5)
        
        ttk.Label(form_frame, text="Password:").grid(row=1, column=0, padx=5)
        password = ttk.Entry(form_frame, show="*")
        password.grid(row=1, column=1, padx=5)
        
        ttk.Label(form_frame, text="Full Name:").grid(row=2, column=0, padx=5)
        full_name = ttk.Entry(form_frame)
        full_name.grid(row=2, column=1, padx=5)
        
        ttk.Label(form_frame, text="Email:").grid(row=3, column=0, padx=5)
        email = ttk.Entry(form_frame)
        email.grid(row=3, column=1, padx=5)
        
        ttk.Label(form_frame, text="Role:").grid(row=4, column=0, padx=5)
        role_combo = ttk.Combobox(form_frame, values=["Student", "Organizer", "Admin", "Teacher"])
        role_combo.grid(row=4, column=1, padx=5)
        
        def add_user():
            try:
                if not all([username.get(), password.get(), full_name.get(), email.get(), role_combo.get()]):
                    messagebox.showerror("Error", "All fields are required!", parent=parent)
                    return
                hashed_password = self.db.hash_password(password.get())
                self.db.cursor.execute(
                    """INSERT INTO Users (username, password_hash, role, full_name, email)
                    VALUES (:v1, :v2, :v3, :v4, :v5)""",
                    {'v1': username.get(), 'v2': hashed_password, 'v3': role_combo.get(), 'v4': full_name.get(), 'v5': email.get()}
                )
                self.db.conn.commit()
                messagebox.showinfo("Success", "User added successfully!", parent=parent)
                refresh_users()
            except cx_Oracle.DatabaseError as e:
                error_obj, = e.args
                messagebox.showerror("Error", f"Failed to add user: ORA-{error_obj.code}: {error_obj.message}", parent=parent)
        
        ttk.Button(form_frame, text="Add User", command=add_user).grid(row=5, column=0, columnspan=2, pady=10)

    def create_student_events(self, parent):
        frame = ttk.Frame(parent, padding="10")
        frame.pack(fill="both", expand=True)
        
        self.no_events_label = ttk.Label(frame, text="No scheduled events available.", font=("Helvetica", 12))
        self.no_events_label.pack(pady=10)
        
        tree = ttk.Treeview(frame, columns=("ID", "Name", "Date", "Time", "Venue", "Club", "Status"), show="headings")
        tree.heading("ID", text="ID")
        tree.heading("Name", text="Event Name")
        tree.heading("Date", text="Date")
        tree.heading("Time", text="Time")
        tree.heading("Venue", text="Venue")
        tree.heading("Club", text="Club")
        tree.heading("Status", text="Status")
        tree.pack(fill="both", expand=True)
        
        button_frame = ttk.Frame(frame)
        button_frame.pack(pady=10, fill="x")
        
        def refresh_events():
            try:
                for item in tree.get_children():
                    tree.delete(item)
                sql = """
                    SELECT e.event_id, e.event_name, TO_CHAR(e.event_date, 'YYYY-MM-DD'), e.event_time, e.venue, c.club_name, format_event_status(e.event_status)
                    FROM Events e
                    JOIN Clubs c ON e.club_id = c.club_id
                    WHERE e.event_status = :v1
                """
                self.db.cursor.execute(sql, {'v1': 'Scheduled'})
                rows = self.db.cursor.fetchall()
                print(f"Student events fetched: {rows}")
                for row in rows:
                    tree.insert("", "end", values=row)
                if rows:
                    self.no_events_label.pack_forget()
                else:
                    self.no_events_label.pack(pady=10)
            except cx_Oracle.DatabaseError as e:
                error_obj, = e.args
                messagebox.showerror("Error", f"Failed to refresh events: ORA-{error_obj.code}: {error_obj.message}", parent=parent)
        
        def register_event():
            selected = tree.selection()
            if not selected:
                messagebox.showerror("Error", "Please select an event to register!", parent=parent)
                return
            event_id = tree.item(selected)["values"][0]
            try:
                self.db.cursor.execute(
                    "INSERT INTO EventRegistrations (event_id, user_id) VALUES (:v1, :v2)",
                    {'v1': event_id, 'v2': self.current_user}
                )
                self.db.conn.commit()
                messagebox.showinfo("Success", "Registered successfully!", parent=parent)
                if hasattr(self, 'registrations_frame'):
                    self.create_registrations_management(self.registrations_frame)
            except cx_Oracle.DatabaseError as e:
                error_obj, = e.args
                messagebox.showerror("Error", f"Registration failed: ORA-{error_obj.code}: {error_obj.message}", parent=parent)
        
        ttk.Button(button_frame, text="Register for Event", command=register_event).pack(side="left", padx=5)
        ttk.Button(button_frame, text="Refresh Events", command=refresh_events).pack(side="left", padx=5)
        refresh_events()

    def create_registrations_management(self, parent):
        self.registrations_frame = parent
        frame = ttk.Frame(parent, padding="10")
        frame.pack(fill="both", expand=True)
        
        tree = ttk.Treeview(frame, columns=("ID", "Event", "Date"), show="headings")
        tree.heading("ID", text="Registration ID")
        tree.heading("Event", text="Event Name")
        tree.heading("Date", text="Registration Date")
        tree.pack(fill="both", expand=True)
        
        def refresh_registrations():
            try:
                for item in tree.get_children():
                    tree.delete(item)
                sql = """
                    SELECT er.registration_id, e.event_name, TO_CHAR(er.registered_at, 'YYYY-MM-DD HH24:MI:SS')
                    FROM EventRegistrations er
                    JOIN Events e ON er.event_id = e.event_id
                    WHERE er.user_id = :v1
                """
                self.db.cursor.execute(sql, {'v1': self.current_user})
                for row in self.db.cursor.fetchall():
                    tree.insert("", "end", values=row)
            except cx_Oracle.DatabaseError as e:
                error_obj, = e.args
                messagebox.showerror("Error", f"Failed to refresh registrations: ORA-{error_obj.code}: {error_obj.message}", parent=parent)
        
        refresh_registrations()
        
        form_frame = ttk.Frame(frame)
        form_frame.pack(pady=10, fill="x")
        
        ttk.Label(form_frame, text="Feedback:").grid(row=0, column=0, padx=5)
        feedback = ttk.Entry(form_frame)
        feedback.grid(row=0, column=1, padx=5)
        
        def submit_feedback():
            selected = tree.selection()
            if not selected:
                messagebox.showerror("Error", "Please select a registration to submit feedback!", parent=parent)
                return
            registration_id = tree.item(selected)["values"][0]
            try:
                self.db.cursor.execute(
                    "UPDATE EventRegistrations SET feedback = :v1 WHERE registration_id = :v2",
                    {'v1': feedback.get(), 'v2': registration_id}
                )
                self.db.conn.commit()
                messagebox.showinfo("Success", "Feedback submitted!", parent=parent)
            except cx_Oracle.DatabaseError as e:
                error_obj, = e.args
                messagebox.showerror("Error", f"Feedback submission failed: ORA-{error_obj.code}: {error_obj.message}", parent=parent)
        
        ttk.Button(form_frame, text="Submit Feedback", command=submit_feedback).grid(row=1, column=0, columnspan=2, pady=10)

    def create_notifications_management(self, parent):
        frame = ttk.Frame(parent, padding="10")
        frame.pack(fill="both", expand=True)
        
        tree = ttk.Treeview(frame, columns=("ID", "Message", "Date", "Status"), show="headings")
        tree.heading("ID", text="ID")
        tree.heading("Message", text="Message")
        tree.heading("Date", text="Date")
        tree.heading("Status", text="Status")
        tree.pack(fill="both", expand=True)
        
        def refresh_notifications():
            try:
                for item in tree.get_children():
                    tree.delete(item)
                sql = """
                    SELECT notification_id, message, TO_CHAR(sent_at, 'YYYY-MM-DD HH24:MI:SS'), is_read
                    FROM Notifications
                    WHERE recipient_id = :v1
                """
                self.db.cursor.execute(sql, {'v1': self.current_user})
                for row in self.db.cursor.fetchall():
                    status = "Read" if row[3] else "Unread"
                    tree.insert("", "end", values=(row[0], row[1], row[2], status))
            except cx_Oracle.DatabaseError as e:
                error_obj, = e.args
                messagebox.showerror("Error", f"Failed to refresh notifications: ORA-{error_obj.code}: {error_obj.message}", parent=parent)
        
        def mark_as_read():
            selected = tree.selection()
            if not selected:
                messagebox.showerror("Error", "Please select a notification to mark as read!", parent=parent)
                return
            notification_id = tree.item(selected)["values"][0]
            try:
                self.db.cursor.execute(
                    "UPDATE Notifications SET is_read = 1 WHERE notification_id = :v1",
                    {'v1': notification_id}
                )
                self.db.conn.commit()
                refresh_notifications()
            except cx_Oracle.DatabaseError as e:
                error_obj, = e.args
                messagebox.showerror("Error", f"Failed to update notification: ORA-{error_obj.code}: {error_obj.message}", parent=parent)
        
        ttk.Button(frame, text="Mark as Read", command=mark_as_read).pack(pady=10)
        refresh_notifications()

    def create_reports_management(self, parent):
        frame = ttk.Frame(parent, padding="10")
        frame.pack(fill="both", expand=True)
        
        tree = ttk.Treeview(frame, columns=("ID", "Event", "Participants", "Feedback"), show="headings")
        tree.heading("ID", text="Report ID")
        tree.heading("Event", text="Event Name")
        tree.heading("Participants", text="Total Participants")
        tree.heading("Feedback", text="Avg Feedback Score")
        tree.pack(fill="both", expand=True)
        
        def refresh_reports():
            try:
                for item in tree.get_children():
                    tree.delete(item)
                sql = """
                    SELECT r.report_id, e.event_name, r.total_participants, r.average_feedback_score
                    FROM Reports r
                    JOIN Events e ON r.event_id = e.event_id
                """
                self.db.cursor.execute(sql)
                for row in self.db.cursor.fetchall():
                    tree.insert("", "end", values=row)
            except cx_Oracle.DatabaseError as e:
                error_obj, = e.args
                messagebox.showerror("Error", f"Failed to refresh reports: ORA-{error_obj.code}: {error_obj.message}", parent=parent)
        
        refresh_reports()

    def create_event_statistics(self, parent):
        frame = ttk.Frame(parent, padding="10")
        frame.pack(fill="both", expand=True)
        
        tree = ttk.Treeview(frame, columns=("Club", "TotalEvents", "AvgRegistrations", "ActiveUsers"), show="headings")
        tree.heading("Club", text="Club Name")
        tree.heading("TotalEvents", text="Total Events")
        tree.heading("AvgRegistrations", text="Avg Registrations per Event")
        tree.heading("ActiveUsers", text="Active Users")
        tree.pack(fill="both", expand=True)
        
        def refresh_stats():
            try:
                for item in tree.get_children():
                    tree.delete(item)
                sql = """
                    SELECT 
                        c.club_name,
                        COUNT(e.event_id) as total_events,
                        COALESCE(AVG((
                            SELECT COUNT(*) 
                            FROM EventRegistrations er 
                            WHERE er.event_id = e.event_id
                        )), 0) as avg_registrations,
                        COUNT(DISTINCT e.organizer_id) as active_users
                    FROM Clubs c
                    LEFT JOIN Events e ON c.club_id = e.club_id
                    WHERE e.event_status = :v1 OR e.event_id IS NULL
                    GROUP BY c.club_id, c.club_name
                    HAVING COUNT(e.event_id) > 0
                """
                self.db.cursor.execute(sql, {'v1': 'Scheduled'})
                rows = self.db.cursor.fetchall()
                print(f"Event statistics fetched: {rows}")
                for row in rows:
                    tree.insert("", "end", values=(row[0], row[1], f"{row[2]:.2f}", row[3]))
            except cx_Oracle.DatabaseError as e:
                error_obj, = e.args
                messagebox.showerror("Error", f"Failed to refresh statistics: ORA-{error_obj.code}: {error_obj.message}", parent=parent)
        
        ttk.Button(frame, text="Refresh Statistics", command=refresh_stats).pack(pady=10)
        refresh_stats()

    def create_user_activity(self, parent):
        frame = ttk.Frame(parent, padding="10")
        frame.pack(fill="both", expand=True)
        
        tree = ttk.Treeview(frame, columns=("Username", "ProposedEvents", "Registrations", "ApprovedEvents"), show="headings")
        tree.heading("Username", text="Username")
        tree.heading("ProposedEvents", text="Proposed Events")
        tree.heading("Registrations", text="Registrations")
        tree.heading("ApprovedEvents", text="Approved Events")
        tree.pack(fill="both", expand=True)
        
        def refresh_activity():
            try:
                for item in tree.get_children():
                    tree.delete(item)
                self.db.cursor.execute("SELECT user_id, username FROM Users")
                for user in self.db.cursor.fetchall():
                    user_id, username = user
                    summary = self.db.generate_user_activity_summary(user_id)
                    if summary:
                        tree.insert("", "end", values=(
                            username,
                            summary['proposed_events'],
                            summary['registrations'],
                            summary['approved_events']
                        ))
            except cx_Oracle.DatabaseError as e:
                error_obj, = e.args
                messagebox.showerror("Error", f"Failed to refresh user activity: ORA-{error_obj.code}: {error_obj.message}", parent=parent)
        
        ttk.Button(frame, text="Refresh Activity", command=refresh_activity).pack(pady=10)
        refresh_activity()

    def create_event_summary(self, parent):
        """Create UI for event summary using PL/SQL (Oracle Version)."""
        frame = ttk.Frame(parent, padding="10")
        frame.pack(fill="both", expand=True)
        
        tree = ttk.Treeview(frame, columns=("Metric", "Value"), show="headings")
        tree.heading("Metric", text="Metric")
        tree.heading("Value", text="Value")
        tree.column("Metric", width=200)
        tree.column("Value", width=200)
        tree.pack(fill="both", expand=True)
        
        ttk.Button(frame, text="Refresh Summary", command=lambda: refresh_summary()).pack(pady=10)
        
        def refresh_summary():
            """Execute PL/SQL to fetch event summary."""
            if not self.db or not self.db.cursor:
                messagebox.showerror("Error", "Database connection not established.", parent=parent)
                return
            try:
                for item in tree.get_children():
                    tree.delete(item)
                
                plsql = """
                DECLARE
                    v_total_events NUMBER;
                    v_pending_events NUMBER;
                    v_avg_registrations NUMBER;
                BEGIN
                    SELECT COUNT(*) INTO v_total_events FROM Events;
                    SELECT COUNT(*) INTO v_pending_events FROM Events WHERE event_status = 'Pending';
                    SELECT AVG(reg_count)
                    INTO v_avg_registrations
                    FROM (
                        SELECT e.event_id, COUNT(er.registration_id) as reg_count
                        FROM Events e
                        LEFT JOIN EventRegistrations er ON e.event_id = er.event_id
                        GROUP BY e.event_id
                    );
                    :v1 := v_total_events;
                    :v2 := v_pending_events;
                    :v3 := v_avg_registrations;
                END;
                """
                total_events = self.db.cursor.var(cx_Oracle.NUMBER)
                pending_events = self.db.cursor.var(cx_Oracle.NUMBER)
                avg_registrations = self.db.cursor.var(cx_Oracle.NUMBER)
                
                print("Executing PL/SQL:", plsql)
                print("Bind variables:", {'v1': total_events, 'v2': pending_events, 'v3': avg_registrations})
                
                self.db.cursor.execute(plsql, {'v1': total_events, 'v2': pending_events, 'v3': avg_registrations})
                self.db.conn.commit()
                
                tree.insert("", "end", values=("Total Events", total_events.getvalue() or 0))
                tree.insert("", "end", values=("Pending Events", pending_events.getvalue() or 0))
                tree.insert("", "end", values=("Average Registrations per Event", f"{avg_registrations.getvalue() or 0:.2f}"))
                
            except cx_Oracle.DatabaseError as e:
                error_obj, = e.args
                errmsg = f"Event summary failed: ORA-{error_obj.code}\n{error_obj.message}"
                print(f"--- ORACLE DB ERROR (refresh_summary) ---")
                print(errmsg)
                traceback.print_exc()
                print(f"--- END ORACLE DB ERROR ---")
                messagebox.showerror("DB Error", errmsg, parent=parent)
            except Exception as e:
                errmsg = f"Unexpected error in event summary: {e}"
                print(f"--- UNEXPECTED ERROR (refresh_summary) ---")
                print(errmsg)
                traceback.print_exc()
                print(f"--- END UNEXPECTED ERROR ---")
                messagebox.showerror("Error", errmsg, parent=parent)
        
        refresh_summary()

if __name__ == "__main__":
    root = tk.Tk()
    app = ClubManagementApp(root)
    root.mainloop()
