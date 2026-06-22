import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QSd

Pane{
    ColumnLayout{
        Layout.fillWidth: true
        Layout.fillHeight: true
        Layout.alignment: Qt.AlignCenter
        Label{text:qsTr("Prompt")}
        MenuSeparator{Layout.fillWidth: true}
        ScrollView{
            Layout.fillWidth: true
            Layout.fillHeight: true
            TextArea{
                id: prompt
                text: "A Man is thinking about telling other peoplke that he is creating a new image generator with c++ and not the python that everyone else uses."
            }
        }
        RowLayout{
            Switch{
                id: autoSaveSwitch
                text: qsTr("save file")
                checked:  false
            }
            Button{
                text: qsTr("Generate Image")
                onClicked: {
                    //ContextParams
                    QSD.ContextParams.diffusionModelPath                = "/srv/ai/ComfyUI/models/unet/ZImage_Turbo/z_image_turbo-Q8_0.gguf"
                    QSD.ContextParams.llmPath                           = "/srv/ai/ComfyUI/models/text_encoders/ZImage_Turbo/Qwen3-4B-Instruct-2507-Q4_K_M.gguf"
                    QSD.ContextParams.vaePath                           = "/srv/ai/ComfyUI/models/vae/ZImage_Turbo/whatever.safetensors"
                    QSD.ContextParams.diffusionFlashAttn                = true
                    QSD.ContextParams.weightsOnCpu                      = true

                    // GenerationParams
                    QSD.ImageGenerationParams.width                          = 512
                    QSD.ImageGenerationParams.height                         = 1024
                    QSD.ImageGenerationParams.seed                           = 42
                    QSD.ImageGenerationParams.prompt                         = prompt.text

                    QSD.ImageGenerationParams.sampleParams.sampleSteps       = 8
                    QSD.ImageGenerationParams.sampleParams.guidance.txtCfg   = parseFloat(1.0)

                    QSD.generateImage(outputImage, autoSaveSwitch.checked)

                }
            }
        }
        /// where we are going to add our cusom time deal
        QSdImage{
            id: outputImage
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

    }
}