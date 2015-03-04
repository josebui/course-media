<?php

class CourseObjectMedia extends CourseObject {

  function take() {
    parent::take();
    $options = $this->getOptions();

    // Get view mode
    $view_mode = $options['media_view_mode'];

    // Get file media view
    $file = file_load($options['media']['fid']);
    $view = file_view_file($file, $view_mode);

    // Set Fulfillment when media is shown 
    $this->getFulfillment()->setComplete()->save();

    return $view;
  }

  function getTakeType() {
    return 'content';
  }

  /**
   * Course media options.
   */
  public function optionsDefinition() {
    $options = parent::optionsDefinition();

    // Media default value
    $options['media'] = '';
    $options['media_view_mode'] = 'media_original';
    return $options;
  }

  /**
   * Add options only for media
   */
  public function optionsForm(&$form, &$form_state) {
    parent::optionsForm($form, $form_state);
    $defaults = $this->getOptions();

    // Media view mode
    // TODO get view modes from media module.
    $form['media_form']['media_view_mode'] = array(
      '#type' => 'select',
      '#title' => t('View mode'),
      '#options' => array(
        'media_original'=> t('Original'),
        'media_link' => t('Link'),
        'media_preview' => t('Preview'),
        'media_small'=> t('Small'),
        'media_large'=> t('Large')
      ),
      '#default_value' => $defaults['media_view_mode']
    );

    // Media form
    $form['media_form']['media'] = array(
      '#type' => 'media',
      '#title' => 'Media',
      '#description' => 'Select media for Course object',
      '#tree' => true,
      '#default_value' => $defaults['media'], 
      '#media_options' => array(
        'global' => array(
          'file_directory' => 'media',
        ),
      )
    );
  }
}
