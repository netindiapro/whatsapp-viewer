#include <wx/wx.h>
#include <wx/mstream.h>
#include <wx/xrc/xmlres.h>

#include "MessagePanel.h"

#include "../whatsapp/Message.h"

namespace UI {

MessagePanel::MessagePanel(wxWindow *parent, const WhatsApp::Message *message) {
  wxXmlResource::Get()->LoadPanel(this, parent, _("MessagePanel"));
  XRCCTRL(*this, "message", wxStaticText)->SetLabelText(message->getData());

  auto thumbnail = message->getThumbnail();
  if (thumbnail) {
    wxMemoryInputStream stream(thumbnail->c_str(), thumbnail->length());
    wxImage image(stream);

    if (image.IsOk()) {
      image.Rescale(image.GetWidth() * 2, image.GetHeight() * 2);

      wxBitmap bitmap(image);
      XRCCTRL(*this, "thumbnail", wxStaticBitmap)->SetBitmap(bitmap);
    }
  }
}

} // namespace UI
