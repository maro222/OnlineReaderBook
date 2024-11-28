# Online Book Reader Project

## Functional Requirements

### User Types
1. **Admin User**
   - Adds books to the system.
   - Cannot sign up (preloaded in the system).

2. **Customer User**
   - Can sign up and log in.
   - Can perform the following actions:
     - View profile with basic information.
     - View the list of books and select one to read.
     - Start a reading session for a book:
       - View total pages.
       - Track current page (e.g., 1/5).
       - Navigate through pages (next/previous).
       - Stop reading, saving session progress.
     - View session history, including:
       - Previous sessions for the same book.
       - Resume from the last stopped page.
       - Multiple sessions for the same book (e.g., 3 sessions for "C++ Book").
   - Cannot have parallel reading sessions.
   - On re-login, can access past session data.

---

## Non-Functional Requirements
1. **Usability**: The system should be easy to use and compatible with other systems.
2. **Security**: Ensure secure user data and login processes.
3. **Reliability**: The system should be robust and handle user actions without failure.
4. **Performance**: Ensure quick response times for user actions.
5. **Maintainability**: Easy to update and maintain the system.
6. **Scalability**: The system should support additional users and books as needed.

---

## Project Specifications

### Admin Users
- Preloaded in memory.
- Can add new books to the system.
- Logout functionality available.

### Books
- Some books preloaded into the system.
- Admins can add more books during runtime.

### Customer Users
- Preloaded users in memory, but new customers can sign up.
- Functionalities:
  1. **View Profile**: Displays basic user information.
  2. **List Books**: Shows available books.
  3. **Select Book**: Start a session for a chosen book.
  4. **Manage Sessions**:
     - Start a new session.
     - Resume a session from the last stopped page.
     - Navigate through pages.
     - Stop a session and save progress.
     - View history of reading sessions, including multiple sessions for the same book.
- Session continuity: User sessions persist even after logout/login.

### Session Details
- A session includes:
  - Total pages of the book.
  - Current page position (e.g., "Page 3/10").
  - Navigation: Next and Previous page.
  - Option to stop reading and save progress.
  
---

## Admin Functionalities
1. **Login**: Access admin functionalities.
2. **Add Books**: Add new books to the system, visible to all users.
3. **Logout**: Exit the admin session.

---

## Example Workflow
1. **Admin** logs in and adds new books.
2. **Customer** logs in, views available books, and starts reading.
3. Customer navigates through the book, stops reading, and the session is saved.
4. Customer logs back in later to resume the saved session.
5. New books added by admin become immediately available for all users.
