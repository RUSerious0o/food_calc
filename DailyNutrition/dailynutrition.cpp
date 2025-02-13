#include "dailynutrition.h"
#include "ui_dailynutrition.h"

DailyNutrition::DailyNutrition(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DailyNutrition),
    m_dataStorage(DataStorage::getInstance()),
    foodListWidget(new AllFoodListForm(this)),
    m_calendar(new QCalendarWidget(this)),
    dailyConsWidget(new DailyConsumedFoodWidget(m_calendar->selectedDate(), this)),
//    dailyConsWidget(new DailyConsumedFoodWidget(QDate(2024, 2, 2), this)),
    m_selectedFood(nullptr),
    m_selectedDate(),
    m_selectedTime()
{
    ui->setupUi(this);

    ui->verticalLayout->insertWidget(-1, foodListWidget);
//    ui->verticalLayout->insertWidget(2, dailyConsWidget);

    ui->calendarLayout->addWidget(m_calendar);

    ui->selectedFoodWeightInput->setValidator(new QIntValidator(this));
    ui->userWeightInput->setValidator(new QDoubleValidator(0, 300, 1, this));
    // TODO fixup slot

    ui->hoursComboBox->addItems({ "00" , "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23" });
    ui->minutesComboBox->addItems({ "00", "05", "10", "15", "20", "25", "30", "35", "40", "45", "50", "55" });


    refreshSelectedTime();
    updateSelectedDate();    
    setupSlots();
}

DailyNutrition::~DailyNutrition()
{
    delete ui;
}

void DailyNutrition::updateSelectedDate()
{
    m_selectedDate = m_calendar->selectedDate();
    ui->dateLabel->setText(m_selectedDate.toString("dd.MM.yyyy"));
    m_calendar->hide();

    dailyConsWidget->hide();
    delete dailyConsWidget;
    dailyConsWidget = new DailyConsumedFoodWidget(m_calendar->selectedDate(), this);
    dailyConsWidget->show();
    ui->verticalLayout->insertWidget(2, dailyConsWidget);
}

void DailyNutrition::refreshSelectedTime()
{
    m_selectedTime = QTime::currentTime();
    ui->hoursComboBox->setCurrentIndex(m_selectedTime.hour());
    ui->minutesComboBox->setCurrentIndex(m_selectedTime.minute() / 5);
}

void DailyNutrition::onShowCalendarButtonClicked()
{
    m_calendar->show();
}

void DailyNutrition::onRefreshDateClicked()
{
    m_selectedDate = QDate::currentDate();
    m_calendar->setSelectedDate(m_selectedDate);
}

void DailyNutrition::onFoodSelected(std::shared_ptr<Food> selectedFood)
{
    m_selectedFood = selectedFood;
    ui->selectedFoodNameLabel->setText(selectedFood->name());
    ui->selectedFoodWeightInput->setFocus();
    ui->selectedFoodWeightInput->selectAll();
}

void DailyNutrition::onSelectedTimeHoursChanged(int hours)
{
    m_selectedTime.setHMS(hours, m_selectedTime.minute(), 0);
}

void DailyNutrition::onSelectedTimeMinutesChanged(int minutes)
{
    m_selectedTime.setHMS(m_selectedTime.hour(), minutes * 5, 0);
}

void DailyNutrition::onConsumeFoodButtonClicked()
{
    if(m_selectedFood == nullptr || ui->selectedFoodWeightInput->text().toInt() == 0) {
        return;
    }

    m_dataStorage.addConsumedFood(m_selectedDate, m_selectedTime.hour() * 60 + m_selectedTime.minute(),
                                  m_selectedFood, ui->selectedFoodWeightInput->text().toInt());
}

void DailyNutrition::setupSlots()
{
    connect(m_calendar, &QCalendarWidget::selectionChanged, this, &DailyNutrition::updateSelectedDate);
    connect(ui->showCalendarButton, &QPushButton::clicked, this, &DailyNutrition::onShowCalendarButtonClicked);
    connect(ui->refreshDateButton, &QPushButton::clicked, this, &DailyNutrition::onRefreshDateClicked);
    connect(foodListWidget, &FoodListForm::itemClicked, this, &DailyNutrition::onFoodSelected);
    connect(ui->refreshTimeButton, &QPushButton::clicked, this, &DailyNutrition::refreshSelectedTime);
    connect(ui->hoursComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onSelectedTimeHoursChanged(int)));
    connect(ui->minutesComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onSelectedTimeMinutesChanged(int)));
    connect(ui->consumeFoodButton, &QPushButton::clicked, this, &DailyNutrition::onConsumeFoodButtonClicked);
}


