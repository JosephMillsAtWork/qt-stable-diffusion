# Warning very alpha weekend project


QSd is a high-performance, thread-safe C++ middleware framework designed to embed stable-diffusion.cpp natively into Qt/QML applications.

Rather than relying on heavy Python servers or bloated WebUI wrappers, 
QSd bridges low-level GGML compute modules directly with the Qt Quick Scene Graph (for images). 
By utilizing a zero-copy data architecture, raw pixel buffers generated during inference are uploaded directly to GPU textures as uncompressed frame streams. 
The framework provides a strictly declarative QML front-end(for the GUI) interface backed by an elegant, 
abstract asynchronous pipeline and dynamic property serialization via QMetaObject reflection (when will nvidia cuda ever get to c++26 so we can use native reflection).


The Qml code is pretty easy. THere are three core models.  An Example of running a ZImage-Turbo generation. 

```qml
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QSd
Item{
    ColumnLayout{
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
                    QSD.ContextParams.diffusionModelPath                    = "/srv/ai/ComfyUI/models/unet/ZImage_Turbo/z_image_turbo-Q8_0.gguf"
                    QSD.ContextParams.llmPath                               = "/srv/ai/ComfyUI/models/text_encoders/ZImage_Turbo/Qwen3-4B-Instruct-2507-Q4_K_M.gguf"
                    QSD.ContextParams.vaePath                               = "/srv/ai/ComfyUI/models/vae/ZImage_Turbo/whatever.safetensors"
                    QSD.ContextParams.diffusionFlashAttn                    = true
                    QSD.ContextParams.weightsOnCpu                          = true

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

        QSdImage{
            id: outputImage
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
```


#### QSD 

QSD(QtStable) is This is the main SINGLETON to get access to the Api

#### QSdBaseParam 
Abstract class that is used in all Params clases. Its core job is to be able to convert all the Params objects to and from JSON or YAML. Its how we save "workflows"

#### QSdCtxParams (QSD.ContextParams) 
This is the core ctx for for model loading. More later on the properties and full doc's after the code starts to stablize

#### QSdImgGenParams (QSD.ImageGenerationParams) 
This is the core image generation settings(Params). More later on the properties and full doc's after the code starts to stablize





