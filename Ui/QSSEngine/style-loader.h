#ifndef STYLELOADER_H
#define STYLELOADER_H

#include <QWidget>

/*!
 * @author Marcin Haber
 *
 * This class allows you to set style to the widgets. The way you can use it is very simple. Just look for the example:
 *
 * Example:
 * -> first of all you should create qss file in Ui/QSSEngine/Qss directory. This file shoud has name as widget name is.
 * For example, if you want to create qss file for widget with name widgetName then you should name file like this: widgetName.qss
 * -> after adding new qss file you have to clean your project and rebuild it again in order to copy qss file to destination folder.
 * You can do it manually. Just copy qss file to Build/Data/Qss directory in place where your application was built.
 * -> it's all what you should do. Other work is to load style from qss file. There are several function which allow you to do that.
 *
 * You can create qss file with type in name. Then You can use it to change style in every widget of this type which are children
 * of the parent. The name can be just QLabel.qss or something more complex RedLabel.qss. It is important to call appriopriate
 * type in method and what is in the file.
 */

class StyleLoader
{
public:
    static StyleLoader& styleLoaderInstance();
    void updateStyleSheetForName( QWidget *widget );
    void updateStyleSheetForType( QWidget *widget, const QString& type );

private:
    StyleLoader();
    ~StyleLoader() {}
};

#endif // STYLELOADER_H
