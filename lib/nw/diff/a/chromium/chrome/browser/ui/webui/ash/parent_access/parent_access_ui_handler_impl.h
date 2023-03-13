// Copyright 2021 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_WEBUI_ASH_PARENT_ACCESS_PARENT_ACCESS_UI_HANDLER_IMPL_H_
#define CHROME_BROWSER_UI_WEBUI_ASH_PARENT_ACCESS_PARENT_ACCESS_UI_HANDLER_IMPL_H_

#include <memory>

#include "base/memory/weak_ptr.h"
#include "chrome/browser/ui/webui/ash/parent_access/parent_access_callback.pb.h"
#include "chrome/browser/ui/webui/ash/parent_access/parent_access_ui.mojom.h"
#include "chrome/browser/ui/webui/ash/parent_access/parent_access_ui_handler_delegate.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"
#include "mojo/public/cpp/bindings/receiver.h"

namespace content {
class WebUI;
}  // namespace content

namespace signin {
class AccessTokenFetcher;
struct AccessTokenInfo;
class IdentityManager;
}  // namespace signin

class GoogleServiceAuthError;

namespace ash {

class ParentAccessUIHandlerImpl
    : public parent_access_ui::mojom::ParentAccessUIHandler {
 public:
  // When |delegate| parameter is null, any internal methods that rely
  // on the delegate will log an error and return empty data to the
  // caller.  This can occur in certain browser tests in which no dialog
  // that implements the delegate is created.
  ParentAccessUIHandlerImpl(
      mojo::PendingReceiver<parent_access_ui::mojom::ParentAccessUIHandler>
          receiver,
      signin::IdentityManager* identity_manager,
      ParentAccessUIHandlerDelegate* delegate);
  ParentAccessUIHandlerImpl(const ParentAccessUIHandlerImpl&) = delete;
  ParentAccessUIHandlerImpl& operator=(const ParentAccessUIHandlerImpl&) =
      delete;
  ~ParentAccessUIHandlerImpl() override;

  // parent_access_ui::mojom::ParentAccessUIHandler overrides:
  void GetOAuthToken(GetOAuthTokenCallback callback) override;
  // Called when the message from the parent access server app was received.
  // encoded_parent_access_callback is a base64 encoded protocol buffer with
  // the received message. 'callback' is a mojo callback used to pass the
  // parsed message back to the WebUI.
  void OnParentAccessCallbackReceived(
      const std::string& encoded_parent_access_callback_proto,
      OnParentAccessCallbackReceivedCallback callback) override;
  void GetParentAccessParams(GetParentAccessParamsCallback callback) override;
  void OnParentAccessDone(parent_access_ui::mojom::ParentAccessResult result,
                          OnParentAccessDoneCallback callback) override;
  void GetParentAccessURL(GetParentAccessURLCallback callback) override;

  // Returns nullptr if the parent was not verified.
  const kids::platform::parentaccess::client::proto::ParentAccessToken*
  GetParentAccessTokenForTest();

 private:
  void OnAccessTokenFetchComplete(GetOAuthTokenCallback callback,
                                  GoogleServiceAuthError error,
                                  signin::AccessTokenInfo access_token_info);

  // Used to fetch OAuth2 access tokens.
  signin::IdentityManager* identity_manager_ = nullptr;
  std::unique_ptr<signin::AccessTokenFetcher> oauth2_access_token_fetcher_;
  // Not owned by this class, and provided by the class's creator.  Can be null
  // if the handler is created without a dialog.
  ParentAccessUIHandlerDelegate* delegate_ = nullptr;
  mojo::Receiver<parent_access_ui::mojom::ParentAccessUIHandler> receiver_;

  // The Parent Access Token.  Only set if the parent was verified.
  std::unique_ptr<
      kids::platform::parentaccess::client::proto::ParentAccessToken>
      parent_access_token_;

  base::WeakPtrFactory<ParentAccessUIHandlerImpl> weak_ptr_factory_{this};
};

}  // namespace ash

#endif  // CHROME_BROWSER_UI_WEBUI_ASH_PARENT_ACCESS_PARENT_ACCESS_UI_HANDLER_IMPL_H_
