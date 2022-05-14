# EGUI
First of three projects created for **GUI** classes at Warsaw University of Technology.

### Short description
Basic blog application created in Qt. Task wasn't fully completed, with edit and remove functions missing.

### Full Task

## Task1: Blog application (TRS) in Qt
- Please write a simple Blog Application using Qt (under linux)
- Data should be stored in text files (in *.json format) in selected folder
## Application should store:

- for the users:
  - userId - unique user id - text obtained from the user during user registration
  - email - e-mail address of the user
  - password - password provided by the user
- for the blogs:
  - id - unique blog identifier (text, provided by the blog creator)
  - title - blog title
  - ownerId - id of the blog owner (creator of the blog)
    - list of items: for each of them
    - title: one line of text
    - datetime: exact time of publication (set autmatically from the system time)
    - content: content of the publication

Blog data should be stored in *.json files!

## Application should enable:
- user registration
- login for registered users
- after login:
  - display blog info for logged in user and list of blog entries
  - creation of a new blog entry
  - deletion of a blog entry by the blog owner
  - display content of the selected blog entry
    - title
    - id of the owner
    - date/time of publication
    - title/content

## Application should contains following views (windows/dialogs)
- login view
- registration view
- list of blogs entries view
- entry add/edit/create view

## Important!
The most important part of the task is to make sure the user interface behaves correctly, e.g.:
- You cannot create a user without an id or with id similar to an existing one
- You cannot confirm creating a blog entry if not all mandatory data is filled in
- If list of entries is empty, "remove" button is disabled
- Data is edited using widgets appropriate for that data type
- Regular desktop application look and feel is maintained (e.g. toolbars, menus, item selection)
- Resizing windows does not cause content to disappear or unused empty space to appear in the window
- Code quality is considered during evaluation

