#include "PluginProcessor.h"
#include "PluginEditor.h"

JucebeamAudioProcessorEditor::JucebeamAudioProcessorEditor (JucebeamAudioProcessor& p)
:  AudioProcessorEditor (&p), processor (p)
{
    DOAt = std::make_shared<DOAthread>(p);
    scene.grid.setSource(DOAt);
    scene.grid.startTimerHz(ENERGY_UPDATE_FREQ);

    setSize (GUI_WIDTH, GUI_HEIGHT);

    // processor.addChangeListener (this);
    scene.setBeamColors(beamColours);
    addAndMakeVisible (scene);

    labelBeam1.setText("1", NotificationType::dontSendNotification);
    labelBeam1.setJustificationType(Justification::left);
    labelBeam1.attachToComponent(&steeringBeam1Slider, true);
    addAndMakeVisible(labelBeam1);
    
    labelBeam2.setText("2", NotificationType::dontSendNotification);
    labelBeam2.setJustificationType(Justification::left);
    labelBeam2.attachToComponent(&steeringBeam2Slider, true);
    addAndMakeVisible(labelBeam2);
    
    NormalisableRange<float> parameterRange;
    // Steering direction slider
    parameterRange = processor.steeringBeam[0]->getNormalisableRange();
    steeringBeam1Slider.setRange(parameterRange.start,parameterRange.end,0.01);
    steeringBeam1Slider.setValue(processor.steeringBeam[0]->get());
    scene.beams[0].move(processor.steeringBeam[0]->get());
    scene.beams[0].setStatus(!processor.muteBeam[0]->get());
    steeringBeam1Slider.addListener(this);
    steeringBeam1Slider.setSliderStyle(Slider::LinearHorizontal);
    steeringBeam1Slider.setTextBoxStyle(Slider::TextBoxRight,false,LABEL_WIDTH,LABEL_HEIGHT);
    steeringBeam1Slider.setValue(processor.steeringBeam[0]->get());
    steeringBeam1Slider.setColour(Slider::thumbColourId, beamColours[0]);
    addAndMakeVisible(steeringBeam1Slider);

    parameterRange = processor.steeringBeam[1]->getNormalisableRange();
    steeringBeam2Slider.setRange(parameterRange.start,parameterRange.end,0.01);
    steeringBeam2Slider.setValue(processor.steeringBeam[1]->get());
    scene.beams[1].move(processor.steeringBeam[1]->get());
    scene.beams[1].setStatus(!processor.muteBeam[1]->get());
    steeringBeam2Slider.addListener(this);
    steeringBeam2Slider.setSliderStyle(Slider::LinearHorizontal);
    steeringBeam2Slider.setTextBoxStyle(Slider::TextBoxRight,false,LABEL_WIDTH,LABEL_HEIGHT);
    steeringBeam2Slider.setValue(processor.steeringBeam[1]->get());
    steeringBeam2Slider.setColour(Slider::thumbColourId, beamColours[1]);
    addAndMakeVisible(steeringBeam2Slider);

    steerLabel.setText("STEER", NotificationType::dontSendNotification);
    steerLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(steerLabel);

    widthLabel.setText("WIDTH", NotificationType::dontSendNotification);
    widthLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(widthLabel);

    parameterRange = processor.widthBeam[0]->getNormalisableRange();
    widthBeam1Knob.setRange(parameterRange.start,parameterRange.end,0.01);
    widthBeam1Knob.setValue(processor.widthBeam[0]->get());
    scene.beams[0].scale(processor.widthBeam[0]->get());
    widthBeam1Knob.addListener(this);
    widthBeam1Knob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    widthBeam1Knob.setTextBoxStyle(Slider::TextBoxRight,false,LABEL_WIDTH,LABEL_HEIGHT);
    widthBeam1Knob.setValue(processor.widthBeam[0]->get());
    widthBeam1Knob.setColour(Slider::thumbColourId, beamColours[0]);
    addAndMakeVisible(widthBeam1Knob);

    parameterRange = processor.widthBeam[1]->getNormalisableRange();
    widthBeam2Knob.setRange(parameterRange.start,parameterRange.end,0.01);
    widthBeam2Knob.setValue(processor.widthBeam[1]->get());
    scene.beams[1].scale(processor.widthBeam[1]->get());
    widthBeam2Knob.addListener(this);
    widthBeam2Knob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    widthBeam2Knob.setTextBoxStyle(Slider::TextBoxLeft,false,LABEL_WIDTH,LABEL_HEIGHT);
    widthBeam2Knob.setValue(processor.widthBeam[1]->get());
    widthBeam2Knob.setColour(Slider::thumbColourId, beamColours[1]);
    addAndMakeVisible(widthBeam2Knob);

    panLabel.setText("PAN", NotificationType::dontSendNotification);
    panLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(panLabel);

    parameterRange = processor.panBeam[0]->getNormalisableRange();
    panBeam1Knob.setRange(parameterRange.start,parameterRange.end,0.01);
    panBeam1Knob.setValue(processor.panBeam[0]->get());
    panBeam1Knob.addListener(this);
    panBeam1Knob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    panBeam1Knob.setTextBoxStyle(Slider::TextBoxRight,false,LABEL_WIDTH,LABEL_HEIGHT);
    panBeam1Knob.setValue(processor.panBeam[0]->get());
    panBeam1Knob.setColour(Slider::thumbColourId, beamColours[0]);
    addAndMakeVisible(panBeam1Knob);

    parameterRange = processor.panBeam[0]->getNormalisableRange();
    panBeam2Knob.setRange(parameterRange.start,parameterRange.end,0.01);
    panBeam2Knob.setValue(processor.panBeam[1]->get());
    panBeam2Knob.addListener(this);
    panBeam2Knob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    panBeam2Knob.setTextBoxStyle(Slider::TextBoxLeft,false,LABEL_WIDTH,LABEL_HEIGHT);
    panBeam2Knob.setValue(processor.panBeam[1]->get());
    panBeam2Knob.setColour(Slider::thumbColourId, beamColours[1]);
    addAndMakeVisible(panBeam2Knob);

    levelLabel.setText("LEVEL", NotificationType::dontSendNotification);
    levelLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(levelLabel);

    parameterRange = processor.levelBeam[0]->getNormalisableRange();
    levelBeam1Knob.setRange(parameterRange.start,parameterRange.end,0.1);
    levelBeam1Knob.setValue(processor.levelBeam[0]->get());
    levelBeam1Knob.addListener(this);
    levelBeam1Knob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    levelBeam1Knob.setTextBoxStyle(Slider::TextBoxRight,false,LABEL_WIDTH,LABEL_HEIGHT);
    levelBeam1Knob.setValue(processor.levelBeam[0]->get());
    levelBeam1Knob.setColour(Slider::thumbColourId, beamColours[0]);
    addAndMakeVisible(levelBeam1Knob);

    parameterRange = processor.levelBeam[1]->getNormalisableRange();
    levelBeam2Knob.setRange(parameterRange.start,parameterRange.end,0.1);
    levelBeam2Knob.setValue(processor.levelBeam[1]->get());
    levelBeam2Knob.addListener(this);
    levelBeam2Knob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    levelBeam2Knob.setTextBoxStyle(Slider::TextBoxLeft,false,LABEL_WIDTH,LABEL_HEIGHT);
    levelBeam2Knob.setValue(processor.levelBeam[1]->get());
    levelBeam2Knob.setColour(Slider::thumbColourId, beamColours[1]);
    addAndMakeVisible(levelBeam2Knob);

    muteLabel.setText("MUTE", NotificationType::dontSendNotification);
    muteLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(muteLabel);

    beam1MuteButton.addListener(this);
    beam1MuteButton.setButtonText("1");
    setMuteButtonColor(0);
    addAndMakeVisible(beam1MuteButton);

    beam2MuteButton.addListener(this);
    beam2MuteButton.setButtonText("2");
    setMuteButtonColor(1);
    addAndMakeVisible(beam2MuteButton);
    
    beam1Meter.setSource(p.beamMeters,0,p.beamMetersLock);
    beam1Meter.startTimerHz(BEAM_METER_UPDATE_FREQ);
    addAndMakeVisible(beam1Meter);
    
    beam2Meter.setSource(p.beamMeters,1,p.beamMetersLock);
    beam2Meter.startTimerHz(BEAM_METER_UPDATE_FREQ);
    addAndMakeVisible(beam2Meter);

//     input section
    
    parameterRange = processor.hpfFreq->getNormalisableRange();
    hpfSlider.setRange(parameterRange.start,parameterRange.end,0.01);
    hpfSlider.setValue(processor.hpfFreq->get());
    hpfSlider.addListener(this);
    hpfSlider.setSliderStyle(Slider::LinearHorizontal);
    hpfSlider.setTextBoxStyle(Slider::TextBoxRight,false,LABEL_WIDTH,LABEL_HEIGHT);
    hpfSlider.setValue(processor.hpfFreq->get());
    addAndMakeVisible(hpfSlider);
    
    hpfLabel.setText("HPF", NotificationType::dontSendNotification);
    hpfLabel.setJustificationType(Justification::left);
    hpfLabel.attachToComponent(&hpfSlider, true);
    addAndMakeVisible(hpfLabel);
    
    inputMeter.setSource(processor.inputMeters, processor.inputMetersLock);
    inputMeter.startTimerHz(INPUT_METER_UPDATE_FREQ);
    addAndMakeVisible(inputMeter);
    
    parameterRange = processor.micGain->getNormalisableRange();
    gainSlider.setRange(parameterRange.start,parameterRange.end,0.01);
    gainSlider.setValue(processor.micGain->get());
    gainSlider.addListener(this);
    gainSlider.setSliderStyle(Slider::LinearHorizontal);
    gainSlider.setTextBoxStyle(Slider::TextBoxRight,false,LABEL_WIDTH,LABEL_HEIGHT);
    gainSlider.setValue(processor.micGain->get());
    addAndMakeVisible(gainSlider);
    
    gainLabel.setText("GAIN", NotificationType::dontSendNotification);
    gainLabel.setJustificationType(Justification::left);
    gainLabel.attachToComponent(&gainSlider, true);
    addAndMakeVisible(gainLabel);
    
    // Start DOA Thread
    DOAt->startThread();
    
}

JucebeamAudioProcessorEditor::~JucebeamAudioProcessorEditor()
{
}

//==============================================================================

void JucebeamAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);

}

void JucebeamAudioProcessorEditor::resized()
{

    auto area = getLocalBounds();
    area.removeFromLeft(LEFT_RIGHT_MARGIN);
    area.removeFromRight(LEFT_RIGHT_MARGIN);
    area.removeFromTop(TOP_BOTTOM_MARGIN);
    area.removeFromBottom(TOP_BOTTOM_MARGIN);

    auto sceneArea = area.removeFromTop(SCENE_HEIGHT);
    sceneArea.removeFromRight((area.getWidth()-SCENE_WIDTH)/2);
    sceneArea.removeFromLeft((area.getWidth()-SCENE_WIDTH)/2);
    scene.setBounds(sceneArea);

    area.removeFromTop(STEER_SLIDER_TOP_MARGIN);
    steeringBeam1Slider.setBounds( area.removeFromTop(STEER_SLIDER_HEIGHT).withTrimmedLeft(LABEL_BEAM_WIDTH));
    steeringBeam2Slider.setBounds( area.removeFromTop(STEER_SLIDER_HEIGHT).withTrimmedLeft(LABEL_BEAM_WIDTH));

    steerLabel.setBounds(area.removeFromTop(LABEL_HEIGHT));

    area.removeFromLeft(KNOBS_LEFT_RIGHT_MARGIN);
    area.removeFromRight(KNOBS_LEFT_RIGHT_MARGIN);

    auto knobsArea = area.removeFromTop(KNOB_HEIGHT+KNOB_TOP_MARGIN);
    knobsArea.removeFromTop(KNOB_TOP_MARGIN);
    widthBeam1Knob.setBounds(knobsArea.removeFromLeft(KNOB_WIDTH));
    widthBeam2Knob.setBounds(knobsArea.removeFromRight(KNOB_WIDTH));
    widthLabel.setBounds(knobsArea);

    knobsArea = area.removeFromTop(KNOB_HEIGHT+KNOB_TOP_MARGIN);
    knobsArea.removeFromTop(KNOB_TOP_MARGIN);
    panBeam1Knob.setBounds(knobsArea.removeFromLeft(KNOB_WIDTH));
    panBeam2Knob.setBounds(knobsArea.removeFromRight(KNOB_WIDTH));
    panLabel.setBounds(knobsArea);

    knobsArea = area.removeFromTop(KNOB_HEIGHT+KNOB_TOP_MARGIN);
    knobsArea.removeFromTop(KNOB_TOP_MARGIN);
    levelBeam1Knob.setBounds(knobsArea.removeFromLeft(KNOB_WIDTH));
    levelBeam2Knob.setBounds(knobsArea.removeFromRight(KNOB_WIDTH));
    auto meterArea = knobsArea.removeFromLeft(BEAM_LED_WIDTH+BEAM_LEFT_RIGHT_MARGIN);
    meterArea.removeFromTop(BEAM_TOP_BOTTOM_MARGIN);
    meterArea.removeFromBottom(BEAM_TOP_BOTTOM_MARGIN);
    meterArea.removeFromLeft(BEAM_LEFT_RIGHT_MARGIN);
    beam1Meter.setBounds(meterArea.removeFromLeft(BEAM_LED_WIDTH));
    meterArea = knobsArea.removeFromRight(BEAM_LED_WIDTH+BEAM_LEFT_RIGHT_MARGIN);
    meterArea.removeFromTop(BEAM_TOP_BOTTOM_MARGIN);
    meterArea.removeFromBottom(BEAM_TOP_BOTTOM_MARGIN);
    meterArea.removeFromRight(BEAM_LEFT_RIGHT_MARGIN);
    beam2Meter.setBounds(meterArea.removeFromRight(BEAM_LED_WIDTH));
    levelLabel.setBounds(knobsArea);

    auto mutesArea = area.removeFromTop(MUTE_HEIGHT+MUTE_TOP_MARGIN);
    mutesArea.removeFromTop(MUTE_TOP_MARGIN);
    mutesArea.removeFromLeft(MUTE_LEFT_RIGHT_MARGIN);
    mutesArea.removeFromRight(MUTE_LEFT_RIGHT_MARGIN);
    beam1MuteButton.setBounds(mutesArea.removeFromLeft(MUTE_WIDTH));
    beam2MuteButton.setBounds(mutesArea.removeFromRight(MUTE_WIDTH));
    muteLabel.setBounds(mutesArea);

    area.removeFromTop(INPUT_SECTION_TOP_MARGIN);
    hpfSlider.setBounds(area.removeFromTop(INPUT_HPF_SLIDER_HEIGHT).withTrimmedLeft(INPUT_HPF_LABEL_WIDTH));
    
    auto inputLedArea = area.removeFromTop(INPUT_LED_HEIGHT);
    inputLedArea.removeFromLeft(INPUT_LEFT_RIGHT_MARGIN);
    inputLedArea.removeFromRight(INPUT_LEFT_RIGHT_MARGIN);
    inputMeter.setBounds(inputLedArea);
    
    gainSlider.setBounds(area.removeFromTop(INPUT_GAIN_SLIDER_HEIGHT).withTrimmedLeft(INPUT_GAIN_LABEL_WIDTH));

}

void JucebeamAudioProcessorEditor::setMuteButtonColor(uint8 beamIdx) {
    
    TextButton* beamMuteButton = beamIdx == 0 ? &beam1MuteButton : &beam2MuteButton;
    Colour colour = processor.muteBeam[beamIdx]->get() == 0 ? Colours::darkslategrey : Colours::darkred;
    beamMuteButton->setColour (TextButton::buttonColourId, colour);

}

void JucebeamAudioProcessorEditor::buttonClicked(Button *button)
{

    if(button == &beam1MuteButton)
    {
        *(processor.muteBeam[0]) = 1 - *(processor.muteBeam[0]);
        setMuteButtonColor(0);
        scene.beams[0].setStatus(!processor.muteBeam[0]->get());
    }
    else if(button == &beam2MuteButton)
    {
        *(processor.muteBeam[1]) = 1 - *(processor.muteBeam[1]);
        setMuteButtonColor(1);
        scene.beams[1].setStatus(!processor.muteBeam[1]->get());
    }
}

void JucebeamAudioProcessorEditor::sliderValueChanged(Slider *slider)
{
    if (slider == &steeringBeam1Slider)
    {
        *(processor.steeringBeam[0]) = slider->getValue();
        scene.beams[0].move(slider->getValue());
    }
    else if (slider == &steeringBeam2Slider)
    {
        *(processor.steeringBeam[1]) = slider->getValue();
        scene.beams[1].move(slider->getValue());
    }
    else if (slider == &widthBeam1Knob)
    {
        *(processor.widthBeam[0]) = slider->getValue();
        scene.beams[0].scale(slider->getValue());
    }
    else if (slider == &widthBeam2Knob)
    {
        *(processor.widthBeam[1]) = slider->getValue();
        scene.beams[1].scale(slider->getValue());
    }
    else if (slider == &panBeam1Knob)
    {
        *(processor.panBeam[0]) = slider->getValue();
    }
    else if (slider == &panBeam2Knob)
    {
        *(processor.panBeam[1]) = slider->getValue();
    }
    else if (slider == &levelBeam1Knob)
    {
        *(processor.levelBeam[0]) = slider->getValue();
    }
    else if (slider == &levelBeam2Knob)
    {
        *(processor.levelBeam[1]) = slider->getValue();
    }
    else if(slider == &hpfSlider)
    {
        *(processor.hpfFreq) = slider->getValue();
    }
    else if(slider == &gainSlider)
    {
        *(processor.micGain) = slider->getValue();
    }
}

