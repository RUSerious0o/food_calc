#include "dailynutrition.h"
#include "ui_dailynutrition.h"

DailyNutrition::DailyNutrition(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DailyNutrition),
    m_dataStorage(DataStorage::getInstance()),
    foodListWidget(new AllFoodListForm(this)),
    m_calendar(new QCalendarWidget(this))
{
    ui->setupUi(this);

    ui->verticalLayout->insertWidget(-1, foodListWidget);
    ui->calendarLayout->addWidget(m_calendar);

    ui->selectedTimeLabel->setText(QTime::currentTime().toString("hh:mm"));

    updateSelectedDate();
    setupSlots();
}

DailyNutrition::~DailyNutrition()
{
    delete ui;
}

void DailyNutrition::updateSelectedDate()
{
    ui->dateLabel->setText(m_calendar->selectedDate().toString("dd.MM.yyyy"));
    m_calendar->hide();
}

void DailyNutrition::onShowCalendarButtonClicked()
{
    m_calendar->show();
}

void DailyNutrition::onRefreshDateClicked()
{
    m_calendar->setSelectedDate(QDate::currentDate());
}

void DailyNutrition::setupSlots()
{
    connect(m_calendar, &QCalendarWidget::selectionChanged, this, &DailyNutrition::updateSelectedDate);
    connect(ui->showCalendarButton, &QPushButton::clicked, this, &DailyNutrition::onShowCalendarButtonClicked);
    connect(ui->refreshDateButton, &QPushButton::clicked, this, &DailyNutrition::onRefreshDateClicked);
}


