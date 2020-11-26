#ifndef DIALOGDISPLAYER_HPP
#define DIALOGDISPLAYER_HPP

class QDialog;

class DialogDisplayer
{
    public:
        virtual ~DialogDisplayer() {}

        virtual void displayDialog(QDialog& dialog) = 0;
};

#endif // DIALOGDISPLAYER_HPP
