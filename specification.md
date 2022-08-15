Actions before closing:

* 1 Before closing saved tab or multiple tabs:
  * only close
  * 1.1
  * 1.2
  * 1.3
* 2 Before closing one unsaved tab
  * Warning: Save? Yes,No,Cancel
  * 2.1 Chosen Yes
    * 2.1.1 Editor has associated path:
      * save to path without asking and close tab
    * 2.1.2 Editor is untitled
      * try SaveAs
      * 2.1.2.1 save as path
        * save text and close tab
      * 2.1.2.2 cancel savings
        * tab will not close (cancel)
  * 2.1 Chosen No
    * close tab
  * 2.1 Chosen Cancel
    * no action
* 3 Before closing multiple unsaved tab
  * Warning: Save? Yes,No,Cancel,YesToAll,NoToAll
  * 3.1 Chosen Yes
    * save editor with path or try saveAs untitled; 
    after this tab go to next unsaved
  * 3.2 Chosen No
    * close tab and discard changes;
      after this tab go to next unsaved
  * 3.3 Chosen Cancel
    * break job 
  * 3.4 Chosen YesToAll
    * first save all editors with path, next
    is shown similar dialog but without "YesToAll" button
  * 3.5 Chosen NoToAll
    * discard changes of all unsaved editors 
 

  * 3.1 All editors have associated path:
  * 3.2 All editors are untitled:
  * 3.3 Are both untitled and editors with path
