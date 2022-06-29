# Use cases

Use cases for the X-ray image enchanging application.

Use case: Enhance images
==========

**Primary Actor:** Radiologist, security officer, quality manager

**Scope:** X-ray image enhancer

**Level:** User goal

**Stakeholders and interests:**
-  Radiologist -- wants to enhance X-ray images for further processing in medical purposes
-  Security officer -- wants to enhance X-ray images for better interpretation in security purposes
-  Quality manager -- wants to enhance X-ray images for quality control purposes

**Precondition:** User has images in 8-bit gray-scale bitmap format

**Trigger:** User has taken X-ray images and has opened image enhancing application

**Minimal Guarantee:** Existing images remain untouched

**Success Guarantee:** Images are enhanced

Scenarios
----------

**1. User imports the images**
>
>  A. Invalid file format
>
>    1. System informs which images were invalid

**2. System views the images**

**3. User selects the images to be enhanced**

**4. User selects an image enhancing operation to be performed for the selected images**
>
>  A. No images selected
>
>    1. Image enhancing is not allowed

**5. System processes the operation for the selected images**

**6. User selects the images to be exported**
>
>  A. No images selected
>
>    1. Exporting is not allowed

**7. User chooses to export the enhanced images to a selected destination**

**8. System exports the enhanced images**