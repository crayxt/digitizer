/***************************************************************************
                          mrudocuments.h  -  description
                             -------------------
    begin                : Sat Sep 25 2004
    copyright            : (C) 2004 by 
    email                : mmdigitizer@earthlink.net
    $Log: mrudocuments.h,v $
    Revision 1.3  2005/03/20 01:47:06  markmitch
    After KDevelop 3 restructuring

    Revision 1.3  2004/09/27 04:52:26  markmitch
    KDevelop does not allow renaming source directory to src

    Revision 1.1  2004/09/26 08:42:48  markmitch
    Most recently used document list


 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef MRUDOCUMENTS_H
#define MRUDOCUMENTS_H

#include <qobject.h>
#include <q3ptrlist.h>
#include <qaction.h>

typedef Q3PtrList<QAction> MruDocumentList;

// class that maintains the most recently used document list in the main menu
class MruDocuments : public QObject
{
  Q_OBJECT
  
  public:

    MruDocuments();
    ~MruDocuments();

    // create and attach popup menu during startup, but hide it when it is not needed
    void attachPopupMenu(QMenu* pParentMenu, int m_parentActionId, QSize frameOffset);

    // merge a document that has just been:
    //   -opened (it has a new name)
    //   -saved for the first time (it has a new name)
    //   -resaved but with a new name (it has a new name)
    void mergeDocument(QString doc);

    // are there any documents?
    bool isEmpty();

  public slots:

    // one of the actions in the parent popup menu has been highlighted
    void slotActionHighlighted(int id);

    // the highlighted action in the parent popup menu is leaving the highlighted state
    void slotActionUnhighlighted();

    // mru item was activated
    void slotMruActivated(int id);

  signals:

    // open the mru document that was just chosen
    void mruChosen(QString filename);
    
  private:

    // a document can be either prepended to the begining of the list, or appended to the end
    void appendDocumentToList(QString doc);
    void prependDocumentToList(QString doc);

    // reconnect actions to popup menu
    void reconnectActionsToPopupMenu();
      
    // parent popup menu and action
    QMenu* m_pParentMenu;
    int m_parentActionId;

    // top left of mru frame is at frame offset plus current position of parent popup menu
    QPoint m_frameOffset;

    // popup menu that will contain the most recently used document list. this is hidden until needed
    QMenu* m_pPopup;

    // max size of mru list
    int m_mruMax;
    
    // dynamic list of mru documents has one QAction per document. if a 
    // document is merged more than once, its previous action is removed
    MruDocumentList m_mruDocuments;
};

#endif // MRUDOCUMENTS_H
